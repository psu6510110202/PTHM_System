#include <WiFi.h>
#include <WebServer.h>
#include <ElegantOTA.h>
#include <Preferences.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include <Wire.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>

#include "read_ds18b20.h"
#include "read_max30100.h"
#include "read_dht11.h"

// Task Handles
TaskHandle_t TaskDS18B20;
TaskHandle_t TaskMAX30100;
TaskHandle_t TaskDHT11;
TaskHandle_t buttonTaskHandle = NULL;

// Time tracking variables
unsigned long tsLastPrintECG = 0;
unsigned long tsLastPrintOther = 0;

#define ECG_PRINT_PERIOD_MS 1000  // ECG (AD8232) print period 10 seconds
#define OTHER_PRINT_PERIOD_MS 5000  // Other sensors (DS18B20, MAX30100, DHT11) print period 5 seconds

#define AP_WIFI_SSID "PTHM_AP"
#define AP_WIFI_PASS "password"

#define MQTT_SERVER "192.168.86.202"
#define MQTT_PORT 1883
#define MQTT_NAME "D000005"

#define DEVICE_ID "000005"
#define BUTTON_PIN 12
#define WIFI_TIMEOUT_MS 5000 // 15 seconds timeout for WiFi connection

WebServer server(80);
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
Preferences pref;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200); // UTC+7 (7 * 3600)

String STA_WIFI_SSID, STA_WIFI_PASS, PATIENT_ID;
long unsigned previousMillis_MQTT;
long unsigned previousMillis_Dashboard;
long unsigned previousMillis_Status;
String WIFI_MODE;
String WIFI_IPADDR;
String MQTT_STATUS;


void setupWiFi();
void buttonTask(void *parameter);
void readNVS();
void saveNVS();
void setupWebServer();
void sendValueMQTT();
void sendValueDashboard();

const char *index_html PROGMEM = R"(
<!DOCTYPE html>
<head>
  <meta charset="UTF-8">
  <title>PTHM Config</title>
  <style>
    body { font-family: Arial, sans-serif; background: #f4f4f9; text-align: center; margin: 0; }
    h1 { color: #333; margin-top: 50px; }
    a { display: inline-block; padding: 12px 24px; margin: 20px; background: #007BFF; color: #fff; text-decoration: none; border-radius: 5px; }
    a:hover { background: #0056b3; }
  </style>
</head>
<body>
  <h1>PTHM Sensor Device Configuration</h1>
  <a href="/configuration">Setup</a><br>
  <a href="/update">Firmware Update</a><br>
</body>
</html>
)";


const char *conf_html PROGMEM = R"(
<!DOCTYPE html>
<head>
  <meta charset="UTF-8">
  <title>PTHM Config</title>
  <style>
    body { font-family: Arial, sans-serif; background: #f4f4f9; text-align: center; margin: 0; }
    h1 { color: #333; margin-top: 50px; }
    form { display: inline-block; text-align: left; }
    input[type="text"], input[type="password"] { padding: 10px; margin: 10px; width: 200px; }
    input[type="submit"] { padding: 10px 20px; background: #007BFF; color: #fff; border: none; border-radius: 5px; cursor: pointer; }
    input[type="submit"]:hover { background: #0056b3; }
  </style>
</head>
<body>
  <h1>PTHM Setup Configuration</h1>
  <form action="/setup_conf" method="POST">
    <p>SSID: <input type="text" name="SSID"></p>
    <p>Password: <input type="password" name="PASS"></p>
    <p>Device ID: %s</p>
    <p>Patient ID: <input type="text" name="PATIENT_ID" pattern="^\d{6}$" required></p>
    <input type="submit" value="Save">
  </form>
</body>
</html>
)";

void setup() {
  Serial.begin(115200);
  Wire.begin();
  readNVS();
  setupWiFi(); // Run WiFi setup synchronously to avoid TCP/IP errors
  setupMqttClient();
  setupWebServer();

  initDS18B20();
  initMAX30100();
  initDHT11();

  // xTaskCreatePinnedToCore(TaskOLED, "OLED Task", 4096, NULL, 1, &TaskOLEDHandle, 1);
  xTaskCreatePinnedToCore(buttonTask, "Button Task", 2048, NULL, 1, &buttonTaskHandle, 1);
  xTaskCreatePinnedToCore(TaskReadDS18B20,"TaskDS18B20",2048,NULL,1,&TaskDS18B20,1);
  xTaskCreatePinnedToCore(TaskReadMAX30100,"TaskMAX30100",8192,NULL,1,&TaskMAX30100,0);
  xTaskCreatePinnedToCore(TaskReadDHT11,"TaskDHT11",2048,NULL,1,&TaskDHT11,1);
  ElegantOTA.begin(&server);
  Serial.printf("Device ID: %s | Patient ID: %s\n", DEVICE_ID, PATIENT_ID.isEmpty() ? "[Config Before Use]" : PATIENT_ID.c_str());
}

void loop() {
  ElegantOTA.loop();
  server.handleClient();
  sendValueMQTT();
  sendValueDashboard();
}

void setupWiFi() {
  unsigned long startAttemptTime = millis();
  WIFI_MODE = "STA";
  WiFi.begin(STA_WIFI_SSID.c_str(), STA_WIFI_PASS.c_str());
  if(!STA_WIFI_SSID.isEmpty() && !STA_WIFI_PASS.isEmpty()){
    Serial.print("Connecting to " + String(STA_WIFI_SSID) + " ");
  }
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    WIFI_IPADDR = WiFi.localIP().toString();
    Serial.println("\nConnected to Wi-Fi: " + WIFI_IPADDR);
    timeClient.begin();
  } else {
    WIFI_MODE = "AP";
    Serial.println("\nWi-Fi connection failed. Starting AP mode...");
    WiFi.softAP(AP_WIFI_SSID, AP_WIFI_PASS);
    WIFI_IPADDR = WiFi.softAPIP().toString();
    Serial.println("AP Mode: " + WIFI_IPADDR);
  }
}

void readNVS() {
  pref.begin("Credentials", true);
  STA_WIFI_SSID = pref.getString("SSID", "");
  STA_WIFI_PASS = pref.getString("PASS", "");
  PATIENT_ID = pref.getString("PATIENT_ID", "");
  pref.end();
}

void saveNVS() {
  STA_WIFI_SSID.trim();
  STA_WIFI_PASS.trim();
  PATIENT_ID.trim();
  pref.begin("Credentials", false);
  pref.putString("SSID", STA_WIFI_SSID);
  pref.putString("PASS", STA_WIFI_PASS);
  pref.putString("PATIENT_ID", PATIENT_ID);
  pref.end();
}

void setupWebServer() {
  server.on("/", HTTP_GET, []() { server.send(200, "text/html", index_html); });
  server.on("/configuration", HTTP_GET, []() { 
    char rendered[1024];
    sprintf(rendered, conf_html, DEVICE_ID);
    server.send(200, "text/html", rendered); 
  });
  server.on("/setup_conf", HTTP_POST, []() {
    STA_WIFI_SSID = server.arg("SSID");
    STA_WIFI_PASS = server.arg("PASS");
    PATIENT_ID = server.arg("PATIENT_ID");
    server.send(200, "text/plain", "PTHM Configuration saved, Restarting...");
    saveNVS();
    delay(2000);
    ESP.restart();
  });
  server.begin();
}

void setupMqttClient(){
  MQTT_STATUS = "Off";
  if (WiFi.status() == WL_CONNECTED && !PATIENT_ID.isEmpty()) {
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    Serial.println("Connecting to MQTT broker " + String(MQTT_SERVER) + ":" + String(MQTT_PORT));
    while (!mqttClient.connected()) {
      if (mqttClient.connect(MQTT_NAME)) {
        // String sensorsTopic = "sensor/device/" + String(DEVICE_ID) + "/data";
        Serial.println("Connected to MQTT broker");
        MQTT_STATUS = "On";
      } else {
        Serial.println("Failed to connect to MQTT broker, retrying in 5 seconds...");
        delay(5000);
      }
    }
  }
}
// Function for MAX30100 task
void TaskReadMAX30100(void *pvParameters) {
  while (1) {
    updateMAX30100();
    vTaskDelay(pdMS_TO_TICKS(100)); 
  }
}

// Function for DS18B20 task (Temperature, 5 seconds update)
void TaskReadDS18B20(void *pvParameters) {
  while (1) {
    if (millis() - tsLastPrintOther > OTHER_PRINT_PERIOD_MS) {
      readDS18B20();  // Print Temperature value
      tsLastPrintOther = millis();  // Reset the print timer for other sensors
    }
    vTaskDelay(pdMS_TO_TICKS(130));  // Run every 100ms
  }
}

// Function for DHT11 task (Temperature & Humidity, 5 seconds update)
void TaskReadDHT11(void *pvParameters) {
  while (1) {
    if (millis() - tsLastPrintOther > OTHER_PRINT_PERIOD_MS) {
        readDHT11();  // Print Temperature & Humidity values
        tsLastPrintOther = millis();  // Reset the print timer for other sensors
    }
    vTaskDelay(pdMS_TO_TICKS(140));  // Run every 100ms
  }
}


void buttonTask(void *parameter) {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    unsigned long pressStart = 0;
    // Serial.println("Something wrong here");
    while (true) {
      if (digitalRead(BUTTON_PIN) == LOW) {
        if (millis() - pressStart > 5000) {
          Serial.println("Clearing preferences and restarting...");
          pref.begin("Credentials", false);
          pref.clear();
          pref.end();
          delay(2000);
          ESP.restart();
        }
      } else {
        pressStart = millis();
      }
      vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void sendValueMQTT(){
  if(millis() - previousMillis_MQTT >= 10000){
    previousMillis_MQTT = millis();

    StaticJsonDocument<256> doc;
    doc["heart_rate"] = heartRate;
    doc["blood_oxy"] = spO2;
    doc["body_temp"] = body_temp;
    doc["room_temp"] = room_temp;
    doc["room_humidity"] = room_humid;
    doc["patient_id"] = PATIENT_ID;
    char jsonBuffer[256];
    serializeJson(doc, jsonBuffer);

    String topic = "sensor/device/" + String(DEVICE_ID);
    mqttClient.publish(topic.c_str(), jsonBuffer);
  }
}

void sendValueDashboard(){
  if(millis() - previousMillis_Dashboard >= 10000){
    previousMillis_Dashboard = millis();
    timeClient.update();
    time_t rawTime = timeClient.getEpochTime();
    struct tm *timeInfo = gmtime(&rawTime); // Convert to human-readable format
    int year =  timeInfo->tm_year + 1900;
    int month =  timeInfo->tm_mon + 1;
    int day = timeInfo->tm_mday;
    int hour = timeInfo->tm_hour;
    int minute = timeInfo->tm_min;

    char buffer[100]; // Buffer to hold the formatted string

    String SENSOR_STATUS = (dht11_status && max30100_status && ds18b20_status ? "Good" : "Bad");
    snprintf(buffer, sizeof(buffer), 
         "%02d/%02d/%04d;%02d:%02d;%2d;%.2f;%.2f;%.2f;%.2f;%s;%s;%s;%s;\n", 
         day, month, year, hour, minute, 
         heartRate, spO2, body_temp, room_temp, room_humid,
         WIFI_MODE, WIFI_IPADDR, MQTT_STATUS, SENSOR_STATUS
    );
    Serial.write(buffer);
  }
}



#include <WiFi.h>
#include <WebServer.h>
#include <ElegantOTA.h>
#include <Preferences.h>
#include <ArduinoJson.h>

#define AP_WIFI_SSID "PTHM_AP"
#define AP_WIFI_PASS "password"
#define DEVICE_ID "000006"
#define BUTTON_PIN 14

WebServer server(80);
Preferences pref;

String STA_WIFI_SSID = "";
String STA_WIFI_PASS = "";
String PATIENT_ID = "";

TaskHandle_t wifiTaskHandle = NULL;
TaskHandle_t buttonTaskHandle = NULL;
SemaphoreHandle_t wifiSemaphore;

void setupWiFiTask(void *parameter);
void buttonTask(void *parameter);
void readNVS();
void saveNVS();
void setupWebServer();

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
  <a href="/WiFi_config">WiFi Setup</a><br>
  <a href="/update">Firmware Update</a><br>
  <a href="/id_config">Patient ID Setup</a>
</body>
</html>
)";


const char *wifi_html PROGMEM = R"(
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
  <h1>Wi-Fi Credentials Setup</h1>
  <form action="/setCredentials" method="POST">
    <p>SSID: <input type="text" name="SSID"></p>
    <p>Password: <input type="password" name="PASS"></p>
    <input type="submit" value="Save">
  </form>
</body>
</html>
)";

const char *id_html PROGMEM = R"(
<!DOCTYPE html>
<head>
  <meta charset="UTF-8">
  <title>PTHM Config</title>
  <style>
    body { font-family: Arial, sans-serif; background: #f4f4f9; text-align: center; margin: 0; }
    h1 { color: #333; margin-top: 50px; }
    form { display: inline-block; text-align: left; }
    input[type="text"] { padding: 10px; margin: 10px; width: 200px; }
    input[type="submit"] { padding: 10px 20px; background: #007BFF; color: #fff; border: none; border-radius: 5px; cursor: pointer; }
    input[type="submit"]:hover { background: #0056b3; }
  </style>
</head>
<body>
  <h1>Patient ID Setup</h1>
  <form action="/setPatient_ID" method="POST">
    <p>Device ID: %s</p>
    <p>Patient ID: <input type="text" name="PATIENT_ID" pattern="^\d{6}$" required></p>
    <input type="submit" value="Save">
  </form>
</body>
</html>
)";



void setup() {
    Serial.begin(115200);
    readNVS();
    wifiSemaphore = xSemaphoreCreateMutex();
    setupWiFiTask(NULL); // Run WiFi setup synchronously to avoid TCP/IP errors
    setupWebServer();
    xTaskCreatePinnedToCore(buttonTask, "Button Task", 2048, NULL, 1, &buttonTaskHandle, 1);
    ElegantOTA.begin(&server);
}

void loop() {
    ElegantOTA.loop();
    server.handleClient();
}

void setupWiFiTask(void *parameter) {
    WiFi.mode(WIFI_AP_STA);

    if (STA_WIFI_SSID.isEmpty() && STA_WIFI_PASS.isEmpty()) {
        Serial.println("No Wi-Fi credentials found, starting AP mode...");
        WiFi.softAP(AP_WIFI_SSID, AP_WIFI_PASS);
        Serial.println("Wi-Fi AP started, SSID: " + String(AP_WIFI_SSID) + " IP: " + WiFi.softAPIP().toString());
    } else {
        WiFi.begin(STA_WIFI_SSID, STA_WIFI_PASS);
        if (WiFi.waitForConnectResult() != WL_CONNECTED) {
            Serial.println("Failed to connect to Wi-Fi network, starting AP mode...");
            WiFi.disconnect();
            WiFi.softAP(AP_WIFI_SSID, AP_WIFI_PASS);
            Serial.println("Wi-Fi AP started, SSID: " + String(AP_WIFI_SSID) + " IP: " + WiFi.softAPIP().toString());
        } else {
            Serial.println("Wi-Fi connected, browse to http://" + WiFi.localIP().toString());
        }
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
    server.on("/WiFi_config", HTTP_GET, []() { server.send(200, "text/html", wifi_html); });
    server.on("/setCredentials", HTTP_POST, []() {
        STA_WIFI_SSID = server.arg("SSID");
        STA_WIFI_PASS = server.arg("PASS");
        server.send(200, "text/plain", "Wi-Fi Credentials saved, Restarting...");
        saveNVS();
        delay(2000);
        ESP.restart();
    });
    server.on("/id_config", HTTP_GET, []() {
      char rendered[1024];
      sprintf(rendered, id_html, DEVICE_ID);
      server.send(200, "text/html", rendered);
    });
    server.on("/setPatient_ID", HTTP_POST, []() {
        PATIENT_ID = server.arg("PATIENT_ID");
        server.send(200, "text/plain", "Patient ID has been set.");
        saveNVS();
        delay(2000);
        server.send(200, "text/html", index_html);
    });
    server.begin();
}

void buttonTask(void *parameter) {
    pinMode(BUTTON_PIN, INPUT);
    unsigned long pressStart = 0;
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
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

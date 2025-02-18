#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>  // Include time.h for proper time struct handling

#define AP_WIFI_SSID "PTHM_AP"
#define AP_WIFI_PASS "password"

String STA_WIFI_SSID = "";
String STA_WIFI_PASS = "";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200); // UTC+7 (7 * 3600)

void setup() {
  Serial.begin(115200);
  WiFi.begin(STA_WIFI_SSID, STA_WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500), Serial.print(".");
  timeClient.begin();
}

void loop() {
  timeClient.update();
  time_t rawTime = timeClient.getEpochTime();
  struct tm *timeInfo = gmtime(&rawTime); // Convert to human-readable format

  int year =  timeInfo->tm_year + 1900;
  int month =  timeInfo->tm_mon + 1;
  int day = timeInfo->tm_mday;
  int hour = timeInfo->tm_hour;
  int minute = timeInfo->tm_min;

  int heartRate = random(60, 121);
  float spo2 = random(9000, 10000) / 100.0;
  float body_temp = random(2800, 4500) / 100.0;
  float room_temp = random(1500, 3500) / 100.0;
  float room_humid = random(5000, 7000) / 100.0;

  char buffer[100]; // Buffer to hold the formatted string

  snprintf(buffer, sizeof(buffer), "%02d/%02d/%04d;%02d:%02d;%2d;%.2f;%.2f;%.2f;%.2f;\n", 
          day, month, year, hour, minute, 
          heartRate, spo2, body_temp, room_temp, room_humid
  );

  Serial.write(buffer, strlen(buffer)); // Send the string as bytes
  delay(1000);
}

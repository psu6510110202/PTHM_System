#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "";
const char* password = "";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200); // UTC+7 (7 * 3600)

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500), Serial.print(".");
  Serial.println("\nWiFi connected.");

  timeClient.begin();
  timeClient.update();

  Serial.printf("%04d-%02d-%02d %02d:%02d:%02d\n", 
                timeClient.getEpochTime() / 86400 + 1970, 
                (timeClient.getEpochTime() % 31556926) / 2629743 + 1, 
                (timeClient.getEpochTime() % 2629743) / 86400 + 1, 
                timeClient.getHours(), 
                timeClient.getMinutes(), 
                timeClient.getSeconds());
}

void loop() {}

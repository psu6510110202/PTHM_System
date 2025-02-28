#include "test_oled_i2c.h"

// Define the global instance of TestOLED
TestOLED oled;

TestOLED::TestOLED() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void TestOLED::begin() {
    Serial.begin(9600);
    delay(250); // wait for the OLED to power up
    display.begin(I2C_ADDRESS, true); // Address 0x3C default
    display.display();
    delay(2000);
    display.clearDisplay();
}

void TestOLED::displayOLED(const String &mode, const String &ip, const String &mqtt, const String &sensor) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.println("WiFi Mode: " + mode);
    display.println();
    display.println("IPAddr: " + ip);
    display.println();
    display.println("MQTT : " + mqtt);
    display.println();
    display.println("Sensor Status : " + sensor);
    display.display();
}

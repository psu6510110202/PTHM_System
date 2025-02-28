#ifndef TEST_OLED_H
#define TEST_OLED_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define I2C_ADDRESS 0x3C // Initialize with the I2C addr 0x3C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // QT-PY / XIAO

class TestOLED {
public:
    TestOLED();
    void begin();
    void displayOLED(const String &mode, const String &ip, const String &mqtt, const String &sensor);

private:
    Adafruit_SH1106G display;
};

// Declare an external instance of the class
extern TestOLED oled;

#endif

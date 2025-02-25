#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()   {

  Serial.begin(9600);

  delay(250); // wait for the OLED to power up
  display.begin(i2c_Address, true); // Address 0x3C default
  //display.setContrast (0); // dim display

  display.display();
  delay(2000);
  display.clearDisplay();
  
  // display.setTextSize(1);
  // display.setTextColor(SH110X_WHITE);
  // display.setCursor(0, 0);
  // display.println("WiFi Mode: AP");
  // display.println();
  // // display.setTextSize(2);
  // display.println("IPAddr: 192.168.13.25");
  // display.println();
  // // display.setTextSize(2);
  // display.println("MQTT : Connected");
  // display.println();
  // display.println("Sensor Status : OK");
  // display.display();
}

void loop(){
  displayOLED("-", "-", "-", "-");
  delay(5000);
  displayOLED("AP", "192.168.13.25", "Connected", "OK");
  delay(5000);
}

void displayOLED(String mode, String ip, String mqtt, String sensor){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("WiFi Mode: " + String(mode));
  display.println();
  display.println("IPAddr: " + String(ip));
  display.println();
  display.println("MQTT : " + String(mqtt));
  display.println();
  display.println("Sensor Status : " + String(sensor));
  display.display();
}
#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Arduino.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_Address 0x3C
#define BUZZER_PIN 5 // Define buzzer pin

extern Adafruit_SH1106G oled;
extern int BPM;
extern int stepDelay;

void init_OLED();  // ฟังก์ชันเริ่มต้นการตั้งค่า
void displayECG(int BGM); // ฟังก์ชันแสดงผล ECG
void displayStatus(String mode, String ip, String mqtt, String sensor);
void clearScreen();

#endif

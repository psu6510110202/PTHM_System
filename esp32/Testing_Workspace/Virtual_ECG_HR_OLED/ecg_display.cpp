#include "ecg_display.h"

Adafruit_SH1106G oled = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
int a = 0, lasta = 0, lastb = SCREEN_HEIGHT / 4;

const int ecgPattern[] = {10, 12, 14, 10, 8, 5, 0, -5, 10, 20, 30, 20, 15, 10, 12, 14, 10};
const int ecgLength = sizeof(ecgPattern) / sizeof(ecgPattern[0]);
int ecgIndex = 0;
int stepDelay;

unsigned long lastBeatTime = 0;
bool beatTriggered = false;
bool buzzerOn = false;
unsigned long buzzerStartTime = 0;
const int buzzerDuration = 100;

void init_OLED() {
    oled.begin(OLED_Address, true);
    oled.clearDisplay();
    oled.display();
    pinMode(BUZZER_PIN, OUTPUT);
}

void displayECG(int BPM) {  // รับ BPM จาก main.cpp
    static int beatInterval = 60000 / BPM;  // เปลี่ยน BPM ได้แบบ dynamic
    if (a > 127) { 
        oled.clearDisplay();
        oled.display();
        a = 0;
        lasta = 0;
    }

    beatInterval = 60000 / BPM;  // อัปเดตจังหวะ heartbeat
    stepDelay = beatInterval / ecgLength;

    int b = ecgPattern[ecgIndex] + 10;
    ecgIndex = (ecgIndex + 1) % ecgLength;  

    oled.setTextColor(SH110X_WHITE);
    oled.drawPixel(a, b, SH110X_WHITE);
    oled.drawLine(lasta, lastb, a, b, SH110X_WHITE);
    oled.display();

    lastb = b;
    lasta = a;

    oled.fillRect(0, 50, 128, 16, SH110X_BLACK);
    oled.setCursor(0, 50);
    oled.setTextSize(2);
    oled.print("BPM: ");
    oled.print(BPM);
    oled.display();
    a++;

    unsigned long currentTime = millis();
    if (currentTime - lastBeatTime >= beatInterval) {
        lastBeatTime = currentTime;
        beatTriggered = true;
    }

    if (beatTriggered) {
        digitalWrite(BUZZER_PIN, HIGH);
        buzzerOn = true;
        buzzerStartTime = millis();
        beatTriggered = false;
    }

    if (buzzerOn && millis() - buzzerStartTime >= buzzerDuration) {
        digitalWrite(BUZZER_PIN, LOW);
        buzzerOn = false;
    }
}

void displayStatus(String mode, String ip, String mqtt, String sensor){
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SH110X_WHITE);
  oled.setCursor(0, 0);
  oled.println("WiFi Mode: " + mode);
  oled.println();
  oled.println("IPAddr: " + ip);
  oled.println();
  oled.println("MQTT : " + mqtt);
  oled.println();
  oled.println("Sensor Status : " + sensor);
  oled.display();
}

void clearScreen(){
  oled.clearDisplay();
}

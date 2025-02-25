#include <Arduino.h>
#include "test_ad8232.h"

#define ECG_PIN 34
#define LO_PLUS 35
#define LO_MINUS 36
#define BUZZER_PIN 27  // ขาของ Buzzer

void initAD8232() {
    Serial.println("Init AD8232");
    pinMode(ECG_PIN, INPUT);
    pinMode(LO_PLUS, INPUT);
    pinMode(LO_MINUS, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);  // กำหนดขา Buzzer เป็น OUTPUT
}

void readAD8232() {
    // อ่านค่า ECG จากเซ็นเซอร์ AD8232
    int ecgValue = analogRead(ECG_PIN);
    int loPlusStatus = digitalRead(LO_PLUS);
    int loMinusStatus = digitalRead(LO_MINUS);

    // แสดงค่าที่อ่านจาก AD8232
    // Serial.printf("ECG: %d | LO+: %d | LO-: %d\n", ecgValue, loPlusStatus, loMinusStatus);

    // // คำนวณการปรับความถี่ของ Buzzer ตามค่า ECG (เพิ่มหรือลดความถี่)
    // int buzzerFrequency = map(ecgValue, 0, 1023, 200, 1000);  // ปรับช่วงความถี่เป็น 200-1000 Hz

    // // หากค่า ECG เป็น 0 (ไม่สามารถอ่านได้หรืออิเล็กโทรดหลุด) ให้ Buzzer ดังยาวๆ
    // if (ecgValue == 0) {
    //     tone(BUZZER_PIN, 1000);  // เสียงดังยาวๆ
    // } else {
    //     tone(BUZZER_PIN, buzzerFrequency);  // ปรับความถี่ตามค่า ECG
    // }

    // // ให้ Buzzer เล่นเสียงในระยะเวลาที่กำหนด
    // delay(100);  // ใช้เวลาประมาณ 100ms ก่อนทำการอ่านค่าใหม่

    // // หยุดเสียง Buzzer เมื่อครบเวลา
    // noTone(BUZZER_PIN);
}

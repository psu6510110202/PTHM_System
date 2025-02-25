#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "test_ds18b20.h"

OneWire oneWire(26);
DallasTemperature sensors(&oneWire);
float body_temp;

void initDS18B20() {
    Serial.println("Init DS18B20");
    sensors.begin();
}

void readDS18B20() {
    sensors.requestTemperatures();
    body_temp = sensors.getTempCByIndex(0);
    
    // ตรวจสอบถ้าอุณหภูมิเป็น -127.00°C (ค่าเริ่มต้นเมื่อเซ็นเซอร์ไม่สามารถอ่านค่าได้)
    if (body_temp == -127.00) {
      body_temp = 0.00;  // กำหนดให้เป็น 0 หากอ่านค่าไม่ได้
    }

    // Serial.printf("Temp: %.2f°C | %.2f°F\n", tempC, sensors.toFahrenheit(tempC));
}

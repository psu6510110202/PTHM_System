#include <Arduino.h>

char buffer[100]; // Buffer for incoming data

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()) {
    int len = Serial.readBytesUntil('\n', buffer, sizeof(buffer) - 1); // Read until newline
    buffer[len] = '\0'; // Null-terminate the string

    int day, month, year, hour, minute, heartRate;
    float spo2, body_temp, room_temp, room_humid;

    sscanf(buffer, "%02d/%02d/%04d;%02d:%02d;%d;%f;%f;%f;%f;", 
           &day, &month, &year, &hour, &minute, 
           &heartRate, &spo2, &body_temp, &room_temp, &room_humid);

    // Print received values
    Serial.printf("Date: %02d/%02d/%04d Time: %02d:%02d\n", day, month, year, hour, minute);
    Serial.printf("Heart Rate: %d bpm, SpO2: %.2f%%\n", heartRate, spo2);
    Serial.printf("Body Temp: %.2f°C, Room Temp: %.2f°C, Humidity: %.2f%%\n", 
                  body_temp, room_temp, room_humid);
  }
}

#include <Wire.h>
#include <Arduino.h>
#include "MAX30100_PulseOximeter.h"
#include "read_max30100.h"

#define PRINT_PERIOD_MS         10000  // Print period of 10 seconds

PulseOximeter pox;
long unsigned tsLastPrint = 0;

// Variables to store the latest heart rate and SpO2 values
int heartRate = 0.0;
float spO2 = 0.0;

int max30100_status;

void initMAX30100() {
  Serial.print("Initializing...");

  // Initialize the PulseOximeter instance
  if (!pox.begin()) {
    Serial.println("MAX30100 was not found. Please check the wiring/power.");
    max30100_status = false;
    while (true);  // Halt execution
  } else {
    max30100_status = true;
    Serial.println("SUCCESS");
  }
}

void updateMAX30100() {

  float currentHeartRate = 3.0, currentSpO2 = 3.0;

  // Update pulse oximeter data
  pox.update();
  currentHeartRate = pox.getHeartRate();
  currentSpO2 = pox.getSpO2();
    
  // Only store values if they are greater than 0 (valid)
  if (currentHeartRate > 0) {
    heartRate = currentHeartRate;
  }
  if (currentSpO2 > 0) {
    spO2 = currentSpO2 > 100 ? 100 : currentSpO2;
  }
}

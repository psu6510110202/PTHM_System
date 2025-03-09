#include <Wire.h>
#include <Arduino.h>
#include "MAX30100_PulseOximeter.h"
#include "esp_task_wdt.h"
#include "test_max30100.h"

#define PRINT_PERIOD_MS         10000  // Print period of 10 seconds
#define WATCHDOG_TIMEOUT_MS     12000  // Watchdog timeout in milliseconds (30 seconds)

PulseOximeter pox;
long unsigned tsLastPrint = 0;

// Variables to store the latest heart rate and SpO2 values
float heartRate = 0.0;
float spO2 = 0.0;

void initMAX30100() {
  Serial.print("Initializing...");

  // Initialize the PulseOximeter instance
  if (!pox.begin()) {
    Serial.println("MAX30100 was not found. Please check the wiring/power.");
    while (true);  // Halt execution
  } else {
    Serial.println("SUCCESS");
  }

  // Configure ESP32 Watchdog Timer
  esp_task_wdt_config_t wdt_config = {
    .timeout_ms = WATCHDOG_TIMEOUT_MS,  // 30 seconds timeout
    .idle_core_mask = 0,                // Apply to core 0 only
    .trigger_panic = true                // Restart ESP32 if watchdog is triggered
  };

  if (esp_task_wdt_reconfigure(&wdt_config) != ESP_OK) {
    Serial.println("Error initializing the watchdog");
  } else {
    Serial.println("Watchdog timer initialized successfully");
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
    spO2 = currentSpO2;
  }

  // Print heart rate and SpO2 levels every 10 seconds
  if (millis() - tsLastPrint > PRINT_PERIOD_MS) {
    // Serial.println("Heart rate: " + String(heartRate) + " bpm / SpO2: " + String(spO2) + "%");
    // Reset the watchdog timer
    esp_task_wdt_reset();
    tsLastPrint = millis();
  }

  // Reset the watchdog timer periodically to prevent reboot
  esp_task_wdt_reset();
}

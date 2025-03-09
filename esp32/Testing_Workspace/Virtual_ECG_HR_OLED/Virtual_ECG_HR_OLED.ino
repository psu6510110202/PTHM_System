#include <Arduino.h>
#include "ecg_display.h"

int BPM = 150;  // Initial BPM

// Task Handle
TaskHandle_t TaskECGHandle = NULL;

// ECG Task (Handles both ECG display & BPM control)
void TaskECG(void *pvParameters) {
  unsigned long lastStatus = millis();
  unsigned long lastECG;
  int displayMode = 0;
  displayStatus("AP", "192.168.86.28", "ON", "GOOD");

  while (1) {
    if((millis() - lastStatus >= 5000) && (displayMode == 0)){
      clearScreen();
      displayMode = 1;
      lastECG = millis();
    } else if ((millis() - lastECG >= 60000) && (displayMode == 1)){
      clearScreen();
      displayMode = 0;
      lastStatus = millis();
    }

    if(displayMode == 1){
      displayECG(BPM);  // Update ECG display
      vTaskDelay(pdMS_TO_TICKS(stepDelay));  // Delay 100ms
    }
    else if(displayMode == 0){
      displayStatus("AP", "192.168.86.28", "ON", "GOOD");
      vTaskDelay(pdMS_TO_TICKS(100));  // Delay 100ms
    }
  }
}

void setup() {
    Serial.begin(115200);
    init_OLED();  // Setup OLED

    // Create a single task for ECG & BPM control
    xTaskCreatePinnedToCore(
        TaskECG,        // Task function
        "ECG Task",     // Task name
        4096,           // Stack size
        NULL,           // No parameters
        1,              // Priority
        &TaskECGHandle, // Task handle
        0               // Run on Core 0
    );
}

void loop() {
    vTaskDelete(NULL); // Disable loop()
}

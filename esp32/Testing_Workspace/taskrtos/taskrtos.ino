#include <Arduino.h>
#include "test_ad8232.h"
#include "test_ds18b20.h"
#include "test_max30100.h"
#include "test_dht11.h"
#include "esp_task_wdt.h"
#include <Wire.h>

// Task Handles
// TaskHandle_t TaskAD8232;
TaskHandle_t TaskDS18B20;
TaskHandle_t TaskMAX30100;
// TaskHandle_t TaskDHT11;

// Time tracking variables
unsigned long tsLastPrintECG = 0;
unsigned long tsLastPrintOther = 0;
unsigned long test = 0; 

#define ECG_PRINT_PERIOD_MS 5000  // ECG (AD8232) print period 10 seconds
#define OTHER_PRINT_PERIOD_MS 5000  // Other sensors (DS18B20, MAX30100, DHT11) print period 5 seconds

// Function for MAX30100 task
void TaskReadMAX30100(void *pvParameters) {
    esp_task_wdt_add(NULL);

    while (1) {
        updateMAX30100();
        esp_task_wdt_reset();
        vTaskDelay(pdMS_TO_TICKS(110)); 
    }
}

// Function for AD8232 task (ECG, 10 seconds update)
// void TaskReadAD8232(void *pvParameters) {
//     while (1) {
//         if (millis() - tsLastPrintECG > ECG_PRINT_PERIOD_MS) {
//             readAD8232();  // Print ECG value
//             tsLastPrintECG = millis();  // Reset the print timer for ECG
//         }
//         vTaskDelay(pdMS_TO_TICKS(120));  // Run every 100ms
//     }
// }

// Function for DS18B20 task (Temperature, 5 seconds update)
void TaskReadDS18B20(void *pvParameters) {
    while (1) {
        if (millis() - tsLastPrintOther > OTHER_PRINT_PERIOD_MS) {
            readDS18B20();  // Print Temperature value
            tsLastPrintOther = millis();  // Reset the print timer for other sensors
        }
        vTaskDelay(pdMS_TO_TICKS(130));  // Run every 100ms
    }
}

// Function for DHT11 task (Temperature & Humidity, 5 seconds update)
// void TaskReadDHT11(void *pvParameters) {
//     while (1) {
//         if (millis() - tsLastPrintOther > OTHER_PRINT_PERIOD_MS) {
//             readDHT11();  // Print Temperature & Humidity values
//             tsLastPrintOther = millis();  // Reset the print timer for other sensors
//         }
//         vTaskDelay(pdMS_TO_TICKS(140));  // Run every 100ms
//     }
// }

void setup() {
    Serial.begin(115200);
    Wire.begin();
    // initAD8232();
    initDS18B20();
    initMAX30100();
    // initDHT11();

    // xTaskCreatePinnedToCore(
    //     TaskReadAD8232,
    //     "TaskAD8232",
    //     2048,
    //     NULL,
    //     1,
    //     &TaskAD8232,
    //     0
    // );

    xTaskCreatePinnedToCore(
        TaskReadDS18B20,
        "TaskDS18B20",
        2048,
        NULL,
        1,
        &TaskDS18B20,
        1
    );

    xTaskCreatePinnedToCore(
        TaskReadMAX30100,
        "TaskMAX30100",
        8192,
        NULL,
        1,
        &TaskMAX30100,
        0
    );
    
    //  xTaskCreatePinnedToCore(
    //     TaskReadDHT11,  // Function to run
    //     "TaskDHT11",   // Task name
    //     2048,             // Stack size
    //     NULL,             // Task parameters
    //     1,                // Priority
    //     &TaskDHT11,    // Task handle
    //     1                 // Run on core 1
    // );
}

void loop() {
    // Empty loop as tasks handle execution
  if(millis() - test >= 5000){
    test = millis();
    Serial.printf("Core: HR: %.2f bpm | SpO2: %.2f%% | BodyTemp: %.2f°C\n", heartRate, spO2, body_temp);
  }
}

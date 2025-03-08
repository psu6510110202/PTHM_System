#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "ui.h"
#include "oled_display.h"
                                                                                                                                                                            
#define T_CS_PIN  13 //--> T_CS

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

#define touchscreen_Min_X 234
#define touchscreen_Max_X 3742
#define touchscreen_Min_Y 172
#define touchscreen_Max_Y 3692

#define LED_PIN 27
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))

TaskHandle_t TaskOLEDHandle;

uint8_t *draw_buf;
uint16_t x, y, z;
uint32_t lastTick = 0;
int Count_Val = 0;
long unsigned previousMillis;
long unsigned lastStatus;
long unsigned lastECG;

int displayMode = 0;
int buffer_hr = 0;

int day, month, year, hour, minute, heartRate;
float spo2, body_temp, room_temp, room_humid;
char wifi_mode[10], wifi_ip[20], mqtt_status[10], sensor_status[10];

XPT2046_Touchscreen touchscreen(T_CS_PIN);

void touchscreen_read(lv_indev_t * indev, lv_indev_data_t * data) {
  if (touchscreen.touched()) {
    TS_Point p = touchscreen.getPoint();
        x = map(p.x, touchscreen_Max_X, touchscreen_Min_X, 1, SCREEN_HEIGHT);
    y = map(p.y, touchscreen_Max_Y, touchscreen_Min_Y, 1, SCREEN_WIDTH);
    z = p.z;
    data->point.x = x;
    data->point.y = y;
    data->state = LV_INDEV_STATE_PRESSED;
  }
  else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

void receive_SensorValues(){
  if (Serial.available() && ((millis() - previousMillis) % 1000) >= 1) {
    char buffer[200];
    int len = Serial.readBytesUntil('\n', buffer, sizeof(buffer) - 1); // Read until newline
    buffer[len] = '\0'; // Null-terminate the string
    Serial.println(buffer);
    sscanf(buffer, "%02d/%02d/%04d;%02d:%02d;%d;%f;%f;%f;%f;%9[^;];%19[^;];%9[^;];%9[^;]",
       &day, &month, &year, &hour, &minute, 
       &heartRate, &spo2, &body_temp, &room_temp, &room_humid,
       wifi_mode, wifi_ip, mqtt_status, sensor_status);
    // Serial.println(String(wifi_mode) + " | " + String(wifi_ip) + " | " + String(mqtt_status) + " | " + String(sensor_status));
  }
}

void update_SensorValues() {
  if (millis() - previousMillis >= 5000) {
    previousMillis = millis();

    char date_buffer[11]; 
    char time_buffer[6];
    buffer_hr = heartRate;  

    snprintf(date_buffer, sizeof(date_buffer), "%02d/%02d/%04d", day, month, year);
    snprintf(time_buffer, sizeof(time_buffer), "%02d:%02d", hour, minute);

    lv_label_set_text(objects.pthm_label_info_date_value_dashboard, date_buffer);
    lv_label_set_text(objects.pthm_label_info_time_value_dashboard, time_buffer);

    lv_label_set_text(objects.pthm_label_heartrate_dashboard, String(heartRate).c_str());
    lv_label_set_text(objects.pthm_label_heartrate_heartpage, String(heartRate).c_str());

    lv_label_set_text(objects.pthm_label_spo2_dashboard, String(spo2).c_str());
    lv_label_set_text(objects.pthm_label_spo2_heartpage, String(spo2).c_str());

    lv_label_set_text(objects.pthm_label_bodytemp_dashboard, String(body_temp).c_str());
    lv_label_set_text(objects.pthm_label_bodytemp_temppage, String(body_temp).c_str());
    lv_arc_set_value(objects.pthm_arc_bodytemp_dashboard, body_temp);
    lv_arc_set_value(objects.pthm_arc_bodytemp_temppage, body_temp);

    lv_label_set_text(objects.pthm_label_roomtemp_dashboard, String(room_temp).c_str());
    lv_label_set_text(objects.pthm_label_roomtemp_roompage, String(room_temp).c_str());

    lv_label_set_text(objects.pthm_label_roomhumid_dashboard, String(room_humid).c_str());
    lv_label_set_text(objects.pthm_label_roomhumid_roompage, String(room_humid).c_str());
  }
}


void basic_Startup(){
  Serial.begin(115200);
  Serial.println();
  delay(3000);

  Serial.println("ESP32 + TFT LCD Touchscreen ILI9341 + LVGL + EEZ Studio");
  Serial.println();
  delay(500);

  String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.println(LVGL_Arduino);
  delay(500);
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println();
  Serial.println("Start LVGL Setup.");
  delay(500);
}

void touchscreen_Startup(){
  touchscreen.begin();
  touchscreen.setRotation(2);
}

void lvgl_Startup(){
  lv_init();
  lv_display_t * disp;
  draw_buf = new uint8_t[DRAW_BUF_SIZE];
  disp = lv_tft_espi_create(SCREEN_HEIGHT, SCREEN_WIDTH, draw_buf, DRAW_BUF_SIZE);
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);
  lv_indev_t * indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, touchscreen_read);

  Serial.println();
  Serial.println("LVGL Setup Completed.");
  delay(500);
}

void setup() {
  basic_Startup();
  touchscreen_Startup();
  lvgl_Startup();
  ui_init();
  init_OLED();

  xTaskCreatePinnedToCore(TaskOLED, "OLED Task", 4096, NULL, 1, &TaskOLEDHandle, 1);
}

void loop() {
  receive_SensorValues();
  update_SensorValues();

  lv_tick_inc(millis() - lastTick); //--> Update the tick timer. Tick is new for LVGL 9.
  lastTick = millis();
  lv_timer_handler(); //--> Update the UI.
  delay(5);
}

void TaskOLED(void *pvParameters) {
  lastStatus = millis();
  strcpy(wifi_mode, "-");
  strcpy(wifi_ip, "-");
  strcpy(mqtt_status, "-");
  strcpy(sensor_status, "-");


  while (1) {
    if((millis() - lastStatus >= 10000) && (displayMode == 0)){
      clearScreen();
      displayMode = 1;
      lastECG = millis();
    } else if ((millis() - lastECG >= 60000) && (displayMode == 1)){
      clearScreen();
      displayMode = 0;
      lastStatus = millis();
    }

    if(displayMode == 1){
      displayECG(buffer_hr);  // Update ECG display
      vTaskDelay(pdMS_TO_TICKS(buffer_hr == 0 ? 150 : stepDelay));  // Delay 100ms
    }
    else if(displayMode == 0){
      displayStatus(wifi_mode, wifi_ip, mqtt_status, sensor_status);
      vTaskDelay(pdMS_TO_TICKS(150));  // Delay 100ms
    }
  }
}
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "ui.h"
#include <WiFi.h>
#include <WebServer.h>
#include <ElegantOTA.h>
#include <Preferences.h>
#include <ArduinoJson.h>
                                                                                                                                                                            
#define T_CS_PIN  13 //--> T_CS

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

#define touchscreen_Min_X 234
#define touchscreen_Max_X 3742
#define touchscreen_Min_Y 172
#define touchscreen_Max_Y 3692

#define LED_PIN 27
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))

uint8_t *draw_buf;
uint16_t x, y, z;
uint32_t lastTick = 0;
int Count_Val = 0;

XPT2046_Touchscreen touchscreen(T_CS_PIN);

void log_print(lv_log_level_t level, const char * buf) {
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}

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

//________________________________________________________________________________ my_image_eez_event_handler()
// Callback that is triggered when "my_image_eez" is clicked.
// static void my_image_eez_event_handler(lv_event_t * e) {
//   lv_event_code_t code = lv_event_get_code(e);  //--> Get the event code.
  
//   if (code == LV_EVENT_CLICKED) {
//     lv_label_set_text(objects.my_label_img_sta, "EEZ image is\nTouched.");
//   }
// }
//________________________________________________________________________________ 

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
  lv_log_register_print_cb(log_print);
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
}

void loop() {
  // put your main code here, to run repeatedly:

  lv_tick_inc(millis() - lastTick); //--> Update the tick timer. Tick is new for LVGL 9.
  lastTick = millis();
  lv_timer_handler(); //--> Update the UI.
  delay(5);
}
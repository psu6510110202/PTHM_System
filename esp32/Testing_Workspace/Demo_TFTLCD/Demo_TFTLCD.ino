//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 02_ESP32_TFT_LCD_TS_ILI9341_LVGL_EEZ_STUDIO
//---------------------------------------- Including Libraries.
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "ui.h"
//---------------------------------------- 

// Defines the T_CS Touchscreen PIN.
#define T_CS_PIN  13 //--> T_CS

// Defines the screen resolution.
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

//---------------------------------------- Defines the Touchscreen calibration result value.
// Replace with the calibration results on your TFT LCD Touchscreen.
#define touchscreen_Min_X 234
#define touchscreen_Max_X 3742
#define touchscreen_Min_Y 172
#define touchscreen_Max_Y 3692
//---------------------------------------- 

#define LED_PIN 27

// LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes.
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint8_t *draw_buf;

// Variables for x, y and z values ​​on the touchscreen.
uint16_t x, y, z;

// Used to track the tick timer.
uint32_t lastTick = 0;

int Count_Val = 0;

// Declaring the "XPT2046_Touchscreen" object as "touchscreen" and its settings.
XPT2046_Touchscreen touchscreen(T_CS_PIN);



//________________________________________________________________________________ log_print()
// If logging is enabled, it will inform the user about what is happening in the library.
void log_print(lv_log_level_t level, const char * buf) {
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}
//________________________________________________________________________________ 



//________________________________________________________________________________ touchscreen_read()
// Get the Touchscreen data.
void touchscreen_read(lv_indev_t * indev, lv_indev_data_t * data) {
  // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z)
  if (touchscreen.touched()) {
    // Get Touchscreen points
    TS_Point p = touchscreen.getPoint();
    
    //---------------------------------------- 
    // Calibrate Touchscreen points with map function to the correct width and height.
    x = map(p.x, touchscreen_Max_X, touchscreen_Min_X, 1, SCREEN_HEIGHT);
    y = map(p.y, touchscreen_Max_Y, touchscreen_Min_Y, 1, SCREEN_WIDTH);
    
    // If the touchscreen on the TFT LCD is upside down, try the code line below.
    // If there is an error on the touchscreen, edit and try other settings in the code section below.
    // Because my TFT LCD Touchscreen device may have different settings from your TFT LCD device.
    //x = map(p.x, touchscreen_Min_X, touchscreen_Max_X, 1, SCREEN_HEIGHT);
    //y = map(p.y, touchscreen_Min_Y, touchscreen_Max_Y, 1, SCREEN_WIDTH);
    //---------------------------------------- 
    
    z = p.z;

    // Set the coordinates.
    data->point.x = x;
    data->point.y = y;

    data->state = LV_INDEV_STATE_PRESSED;

    // Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor.
    /*Serial.print("X = ");
    Serial.print(x);
    Serial.print(" | Y = ");
    Serial.print(y);
    Serial.print(" | Pressure = ");
    Serial.print(z);
    Serial.println();*/
  }
  else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}
//________________________________________________________________________________ 



//________________________________________________________________________________ my_button_test_bar_event_handler()
// Callback that is triggered when "my_button_test_bar" is clicked.
static void my_button_test_bar_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);  //--> Get the event code.
  
  if (code == LV_EVENT_CLICKED) {
    int RandVal = random(0, 100);

    char buf[4];
    lv_snprintf(buf, sizeof(buf), "%d", RandVal);

    lv_bar_set_value(objects.my_vertical_bar, RandVal, LV_ANIM_ON);
    lv_label_set_text(objects.my_label_vertical_bar, buf);
    
    lv_bar_set_value(objects.my_horizontal_bar, RandVal, LV_ANIM_ON);
    lv_label_set_text(objects.my_label_horizontal_bar, buf);
    
    lv_arc_set_value(objects.my_arc_bar, RandVal);
    lv_label_set_text(objects.my_label_arc_bar, buf);
  }
}
//________________________________________________________________________________ 



//________________________________________________________________________________ my_button_toggle_event_handler()
// Callback that is triggered when "my_button_toggle" is clicked.
static void my_button_toggle_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);                      //--> Get the event code.
  lv_obj_t * my_button_toggle = (lv_obj_t*) lv_event_get_target(e); //--> Button that generated the event.
  
  if (code == LV_EVENT_VALUE_CHANGED) {
    LV_UNUSED(my_button_toggle);

    bool checked = lv_obj_has_state(my_button_toggle, LV_STATE_CHECKED);

    // Conditions for changing the button color (my_button_toggle).
    // 0xff + color code in hex.
    // Example :
    // 0xff + ff0000 (red in hex).
    // So for red: 0xffff0000.
    if (checked == true) {
      lv_obj_set_style_bg_color(objects.my_button_toggle, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_CHECKED);
      digitalWrite(LED_PIN, HIGH);
    } else {
      lv_obj_set_style_bg_color(objects.my_button_toggle, lv_color_hex(0xffff7f50), LV_PART_MAIN | LV_STATE_DEFAULT);
      digitalWrite(LED_PIN, LOW);
    }
  }
}
//________________________________________________________________________________ 



//________________________________________________________________________________ my_switch_event_handler()
// Callback that is triggered when "my_switch" is clicked/toggled.
static void my_switch_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);                          //--> Get the event code.
  lv_obj_t * my_switch = (lv_obj_t*) lv_event_get_target(e);            //--> Switch that generated the event.
  lv_obj_t * my_label_switch = (lv_obj_t *)lv_event_get_user_data(e);   //--> Label or other UI elements we want to update (Optional).
  
  if (code == LV_EVENT_VALUE_CHANGED) {
    LV_UNUSED(my_switch);

    bool checked = lv_obj_has_state(my_switch, LV_STATE_CHECKED);

    if (checked == true) {
      lv_label_set_text(my_label_switch, "ON");
      lv_obj_set_style_text_color(my_label_switch, lv_color_hex(0xffff7f50), LV_PART_MAIN | LV_STATE_DEFAULT);
      digitalWrite(LED_PIN, HIGH);
    } else {
      lv_label_set_text(my_label_switch, "OFF");
      lv_obj_set_style_text_color(my_label_switch, lv_color_hex(0xffb6b6b6), LV_PART_MAIN | LV_STATE_DEFAULT);
      digitalWrite(LED_PIN, LOW);
    }
  }
}
//________________________________________________________________________________ 



//________________________________________________________________________________ my_horizontal_slider_value_changed_event_cb()
// Callback to print Slider value (my_horizontal_slider) to Label (my_label_horizontal_slider)
// to be displayed on TFT LCD and change Canvas color.
// This callback is triggered when Slider value changes.
static void my_horizontal_slider_value_changed_event_cb(lv_event_t * e) {
  lv_obj_t * my_horizontal_slider = (lv_obj_t *)lv_event_get_target(e);            //--> Slider that generated the event.
  lv_obj_t * my_label_horizontal_slider = (lv_obj_t *)lv_event_get_user_data(e);   //--> Label or other UI elements we want to update (Optional).
  
  char buf[8];
  lv_snprintf(buf, sizeof(buf), "%d", (int)lv_slider_get_value(my_horizontal_slider));
  lv_label_set_text(my_label_horizontal_slider, buf);
}
//________________________________________________________________________________ 



//________________________________________________________________________________ my_vertical_slider_value_changed_event_cb()
// Callback to print Slider value (my_vertical_slider) to Label (my_label_vertical_slider)
// to be displayed on TFT LCD and change Canvas color.
// This callback is triggered when Slider value changes.
static void my_vertical_slider_value_changed_event_cb(lv_event_t * e) {
  lv_obj_t * my_vertical_slider       = (lv_obj_t *)lv_event_get_target(e);     //--> Slider that generated the event.
  lv_obj_t * my_label_vertical_slider = (lv_obj_t *)lv_event_get_user_data(e);  //--> Label or other UI elements we want to update (Optional).

  char buf[8];
  lv_snprintf(buf, sizeof(buf), "%d", (int)lv_slider_get_value(my_vertical_slider));
  lv_label_set_text(my_label_vertical_slider, buf);
}
//________________________________________________________________________________ 



//________________________________________________________________________________ my_image_esp32_event_handler()
// Callback that is triggered when "my_image_esp32" is clicked.
static void my_image_esp32_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);  //--> Get the event code.
  
  if (code == LV_EVENT_CLICKED) {
    lv_label_set_text(objects.my_label_img_sta, "ESP32 image is\nTouched.");
  }
}
//________________________________________________________________________________ 



//________________________________________________________________________________ my_image_lvgl_event_handler()
// Callback that is triggered when "my_image_lvgl" is clicked.
static void my_image_lvgl_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);  //--> Get the event code.
  
  if (code == LV_EVENT_CLICKED) {
    lv_label_set_text(objects.my_label_img_sta, "LVGL image is\nTouched.");
  }
}
//________________________________________________________________________________ 



//________________________________________________________________________________ my_image_eez_event_handler()
// Callback that is triggered when "my_image_eez" is clicked.
static void my_image_eez_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);  //--> Get the event code.
  
  if (code == LV_EVENT_CLICKED) {
    lv_label_set_text(objects.my_label_img_sta, "EEZ image is\nTouched.");
  }
}
//________________________________________________________________________________ 



//________________________________________________________________________________ 
void setup() {
  // put your setup code here, to run once:

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

  //---------------------------------------- LVGL setup.
  Serial.println();
  Serial.println("Start LVGL Setup.");
  delay(500);
  

  // Start the SPI for the touchscreen and init the touchscreen.
  touchscreen.begin();

  // Set the Touchscreen rotation in landscape mode.
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 0. "touchscreen.setRotation(0);"
  touchscreen.setRotation(2);

  // Start LVGL.
  lv_init();
  
  // Register print function for debugging.
  lv_log_register_print_cb(log_print);

  // Create a display object.
  lv_display_t * disp;
  
  // Initialize the TFT display using the TFT_eSPI library.
  draw_buf = new uint8_t[DRAW_BUF_SIZE];
  disp = lv_tft_espi_create(SCREEN_HEIGHT, SCREEN_WIDTH, draw_buf, DRAW_BUF_SIZE);
  // If the display on the TFT LCD has problems, try the line of code below:
  //disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, DRAW_BUF_SIZE);
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);
    
  // Initialize an LVGL input device object (Touchscreen).
  lv_indev_t * indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  
  // Set the callback function to read Touchscreen input.
  lv_indev_set_read_cb(indev, touchscreen_read);

  Serial.println();
  Serial.println("LVGL Setup Completed.");
  delay(500);
  //---------------------------------------- 

  // Integrate EEZ Studio GUI.
  ui_init();

  // Register "my_button_test_bar" event handler.
  lv_obj_add_event_cb(objects.my_button_test_bar, my_button_test_bar_event_handler, LV_EVENT_ALL, NULL);

  // Register "my_button_toggle" event handler.
  lv_obj_add_event_cb(objects.my_button_toggle, my_button_toggle_event_handler, LV_EVENT_ALL, NULL);

   // Register "my_switch" event handler.
  lv_obj_add_event_cb(objects.my_switch, my_switch_event_handler, LV_EVENT_VALUE_CHANGED, objects.my_label_switch);

  // Register "my_horizontal_slider" event handler.
  lv_obj_add_event_cb(objects.my_horizontal_slider, my_horizontal_slider_value_changed_event_cb, LV_EVENT_VALUE_CHANGED, objects.my_label_horizontal_slider);

  // Register "my_vertical_slider" event handler.
  lv_obj_add_event_cb(objects.my_vertical_slider, my_vertical_slider_value_changed_event_cb, LV_EVENT_VALUE_CHANGED, objects.my_label_vertical_slider);

  // Register "my_image_esp32" event handler.
  lv_obj_add_event_cb(objects.my_image_esp32, my_image_esp32_event_handler, LV_EVENT_ALL, NULL);

  // Register "my_image_lvgl" event handler.
  lv_obj_add_event_cb(objects.my_image_lvgl, my_image_lvgl_event_handler, LV_EVENT_ALL, NULL);

  // Register "my_image_eez" event handler.
  lv_obj_add_event_cb(objects.my_image_eez, my_image_eez_event_handler, LV_EVENT_ALL, NULL);
}
//________________________________________________________________________________ 



//________________________________________________________________________________ 
void loop() {
  // put your main code here, to run repeatedly:

  lv_tick_inc(millis() - lastTick); //--> Update the tick timer. Tick is new for LVGL 9.
  lastTick = millis();
  lv_timer_handler(); //--> Update the UI.
  delay(5);
}
//________________________________________________________________________________ 
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
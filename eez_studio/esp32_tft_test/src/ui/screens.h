#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *my_panet_header;
    lv_obj_t *test;
    lv_obj_t *my_panel_bar;
    lv_obj_t *my_vertical_bar;
    lv_obj_t *my_label_vertical_bar;
    lv_obj_t *my_horizontal_bar;
    lv_obj_t *my_label_horizontal_bar;
    lv_obj_t *my_arc_bar;
    lv_obj_t *my_label_arc_bar;
    lv_obj_t *my_button_test_bar;
    lv_obj_t *my_label_button_test_bar;
    lv_obj_t *my_panel_btn_tgl_switch;
    lv_obj_t *my_button_toggle;
    lv_obj_t *my_label_button;
    lv_obj_t *my_switch;
    lv_obj_t *my_label_switch;
    lv_obj_t *my_panel_slider;
    lv_obj_t *my_horizontal_slider;
    lv_obj_t *my_label_horizontal_slider;
    lv_obj_t *my_vertical_slider;
    lv_obj_t *my_label_vertical_slider;
    lv_obj_t *my_panel_image;
    lv_obj_t *my_image_esp32;
    lv_obj_t *my_image_lvgl;
    lv_obj_t *my_image_eez;
    lv_obj_t *my_label_img_sta;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
};

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
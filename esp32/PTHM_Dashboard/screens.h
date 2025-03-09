#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *heart_page;
    lv_obj_t *temp_page;
    lv_obj_t *room_page;
    lv_obj_t *pthm_panel_menu;
    lv_obj_t *pthm_button_heart_dashboard;
    lv_obj_t *pthm_button_temp_dashboard;
    lv_obj_t *pthm_button_room_dashboard;
    lv_obj_t *pthm_button_dashboard;
    lv_obj_t *obj0;
    lv_obj_t *pthm_panel_heart_dashboard;
    lv_obj_t *pthm_panel_temp_dashboard;
    lv_obj_t *pthm_img_spo2_dashboard;
    lv_obj_t *pthm_label_heartrate_dashboard;
    lv_obj_t *pthm_label_heartrate_unit_dashboard;
    lv_obj_t *pthm_label_spo2_dashboard;
    lv_obj_t *pthm_label_spo2_unit_dashboard;
    lv_obj_t *pthm_panel_temp_dashboard_1;
    lv_obj_t *pthm_panel_info_dashboard;
    lv_obj_t *pthm_img_heartrate_dashboard;
    lv_obj_t *pthm_arc_bodytemp_dashboard;
    lv_obj_t *pthm_label_bodytemp_dashboard;
    lv_obj_t *pthm_label_roomtemp_unit_dashboard;
    lv_obj_t *pthm_img_bodytemp_dashboard;
    lv_obj_t *pthm_img_roomtemp_dashboard;
    lv_obj_t *pthm_img_roomhumid_dashboard_1;
    lv_obj_t *pthm_label_roomtemp_dashboard;
    lv_obj_t *pthm_label_roomtemp_unit_dashboard_1;
    lv_obj_t *pthm_label_roomhumid_dashboard;
    lv_obj_t *pthm_label_roomhumid_unit_dashboard_2;
    lv_obj_t *pthm_label_info_header_dashboard;
    lv_obj_t *pthm_label_info_date_dashboard;
    lv_obj_t *pthm_label_info_time_dashboard;
    lv_obj_t *pthm_img_info_logo_dashboard;
    lv_obj_t *pthm_label_info_date_value_dashboard;
    lv_obj_t *pthm_label_info_time_value_dashboard;
    lv_obj_t *pthm_panel_menu_2;
    lv_obj_t *pthm_button_heart_2;
    lv_obj_t *obj1;
    lv_obj_t *pthm_button_temp_2;
    lv_obj_t *pthm_button_room_2;
    lv_obj_t *pthm_button_dashboard_2;
    lv_obj_t *obj2;
    lv_obj_t *pthm_panel_heart;
    lv_obj_t *pthm_img_spo2_heartpage;
    lv_obj_t *pthm_label_heartrate_heartpage;
    lv_obj_t *pthm_label_heartrate_unit_heartpage;
    lv_obj_t *pthm_label_spo2_heartpage;
    lv_obj_t *pthm_label_spo2_unit_heartpage;
    lv_obj_t *pthm_img_heartrate_heartpage;
    lv_obj_t *pthm_label_heart_header;
    lv_obj_t *pthm_panel_menu_temppage;
    lv_obj_t *pthm_button_heart_temppage;
    lv_obj_t *obj3;
    lv_obj_t *pthm_button_temp_temppage;
    lv_obj_t *pthm_button_room_temppage;
    lv_obj_t *pthm_button_dashboard_temppage;
    lv_obj_t *obj4;
    lv_obj_t *pthm_panel_temp;
    lv_obj_t *pthm_arc_bodytemp_temppage;
    lv_obj_t *pthm_label_temp_header;
    lv_obj_t *pthm_img_bodytemp_temppage;
    lv_obj_t *pthm_label_bodytemp_temppage;
    lv_obj_t *pthm_label_bodytemp_unit_temppage;
    lv_obj_t *pthm_label_bodytemp_min_temppage;
    lv_obj_t *pthm_label_bodytemp_max_temppage;
    lv_obj_t *pthm_panel_menu_roompage;
    lv_obj_t *pthm_button_heart_roompage;
    lv_obj_t *pthm_button_temp_roompage;
    lv_obj_t *pthm_button_ecg_roompage;
    lv_obj_t *obj5;
    lv_obj_t *pthm_button_dashboard_roompage;
    lv_obj_t *obj6;
    lv_obj_t *pthm_panel_room;
    lv_obj_t *pthm_label_roomtemp_roompage;
    lv_obj_t *pthm_label_roomtemp_unit_roompage;
    lv_obj_t *pthm_label_roomhumid_roompage;
    lv_obj_t *pthm_label_roomhumid_unit_roompage;
    lv_obj_t *pthm_label_room_header;
    lv_obj_t *pthm_img_roomtemp_roompage;
    lv_obj_t *pthm_img_roomhumid_roompage;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_HEART_PAGE = 2,
    SCREEN_ID_TEMP_PAGE = 3,
    SCREEN_ID_ROOM_PAGE = 4,
};

void create_screen_main();
void tick_screen_main();

void create_screen_heart_page();
void tick_screen_heart_page();

void create_screen_temp_page();
void tick_screen_temp_page();

void create_screen_room_page();
void tick_screen_room_page();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // pthm_panel_menu
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pthm_panel_menu = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 40);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00b5e2), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_button_heart_dashboard
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_heart_dashboard = obj;
            lv_obj_set_pos(obj, 85, 8);
            lv_obj_set_size(obj, 70, 25);
            lv_obj_add_event_cb(obj, action_event_handler_heart_page, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4a90e2), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Heart");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_button_temp_dashboard
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_temp_dashboard = obj;
            lv_obj_set_pos(obj, 165, 8);
            lv_obj_set_size(obj, 70, 25);
            lv_obj_add_event_cb(obj, action_event_handler_temp_page, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4a90e2), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Temp");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_button_room_dashboard
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_room_dashboard = obj;
            lv_obj_set_pos(obj, 245, 8);
            lv_obj_set_size(obj, 70, 25);
            lv_obj_add_event_cb(obj, action_event_handler_room_page, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4a90e2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Room");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_button_dashboard
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_dashboard = obj;
            lv_obj_set_pos(obj, 3, 8);
            lv_obj_set_size(obj, 75, 25);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffdda518), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj0 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Dashboard");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_panel_heart_dashboard
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pthm_panel_heart_dashboard = obj;
            lv_obj_set_pos(obj, 5, 44);
            lv_obj_set_size(obj, 155, 91);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffb6b6b6), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_panel_temp_dashboard
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pthm_panel_temp_dashboard = obj;
            lv_obj_set_pos(obj, 165, 44);
            lv_obj_set_size(obj, 151, 91);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffb6b6b6), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_img_spo2_dashboard
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pthm_img_spo2_dashboard = obj;
            lv_obj_set_pos(obj, 11, 87);
            lv_obj_set_size(obj, 45, 45);
            lv_img_set_src(obj, &img_img_spo2);
        }
        {
            // pthm_label_heartrate_dashboard
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_heartrate_dashboard = obj;
            lv_obj_set_pos(obj, 62, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "120");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfff70000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_heartrate_unit_dashboard
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_heartrate_unit_dashboard = obj;
            lv_obj_set_pos(obj, 106, 59);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Bpm");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfff70000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_spo2_dashboard
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_spo2_dashboard = obj;
            lv_obj_set_pos(obj, 56, 99);
            lv_obj_set_size(obj, 78, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "99.96");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfff70000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_spo2_unit_dashboard
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_spo2_unit_dashboard = obj;
            lv_obj_set_pos(obj, 137, 99);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "%");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfff70000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_panel_temp_dashboard_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pthm_panel_temp_dashboard_1 = obj;
            lv_obj_set_pos(obj, 7, 139);
            lv_obj_set_size(obj, 125, 97);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffb6b6b6), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_panel_info_dashboard
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pthm_panel_info_dashboard = obj;
            lv_obj_set_pos(obj, 138, 138);
            lv_obj_set_size(obj, 175, 99);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffb6b6b6), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_img_heartrate_dashboard
            lv_obj_t *obj = lv_animimg_create(parent_obj);
            objects.pthm_img_heartrate_dashboard = obj;
            lv_obj_set_pos(obj, 13, 44);
            lv_obj_set_size(obj, 44, 46);
            static const lv_image_dsc_t *images[2] = {
                &img_img_heartrate,
                &img_img_heartrate_sm,
            };
            lv_animimg_set_src(obj, (const void **)images, 2);
            lv_animimg_set_duration(obj, 1000);
            lv_animimg_set_repeat_count(obj, LV_ANIM_REPEAT_INFINITE);
            lv_animimg_start(obj);
        }
        {
            // pthm_arc_bodytemp_dashboard
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.pthm_arc_bodytemp_dashboard = obj;
            lv_obj_set_pos(obj, 27, 145);
            lv_obj_set_size(obj, 80, 80);
            lv_arc_set_range(obj, 28, 45);
            lv_arc_set_value(obj, 35.5);
            lv_arc_set_bg_start_angle(obj, 150);
            lv_arc_set_bg_end_angle(obj, 30);
            lv_obj_set_style_arc_width(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffb6b6b6), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 9, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff3cc905), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 9, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff44df07), LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_bodytemp_dashboard
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_bodytemp_dashboard = obj;
            lv_obj_set_pos(obj, 31, 211);
            lv_obj_set_size(obj, 53, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "35.5");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_roomtemp_unit_dashboard
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_roomtemp_unit_dashboard = obj;
            lv_obj_set_pos(obj, 90, 211);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "C");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_img_bodytemp_dashboard
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pthm_img_bodytemp_dashboard = obj;
            lv_obj_set_pos(obj, 44, 161);
            lv_obj_set_size(obj, 45, 45);
            lv_img_set_src(obj, &img_img_bodytemp);
        }
        {
            // pthm_img_roomtemp_dashboard
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pthm_img_roomtemp_dashboard = obj;
            lv_obj_set_pos(obj, 183, 50);
            lv_obj_set_size(obj, 45, 45);
            lv_img_set_src(obj, &img_img_roomtemp);
        }
        {
            // pthm_img_roomhumid_dashboard_1
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pthm_img_roomhumid_dashboard_1 = obj;
            lv_obj_set_pos(obj, 254, 48);
            lv_obj_set_size(obj, 45, 45);
            lv_img_set_src(obj, &img_img_roomhumid);
        }
        {
            // pthm_label_roomtemp_dashboard
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_roomtemp_dashboard = obj;
            lv_obj_set_pos(obj, 168, 99);
            lv_obj_set_size(obj, 52, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "35.56");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdd7e0f), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_roomtemp_unit_dashboard_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_roomtemp_unit_dashboard_1 = obj;
            lv_obj_set_pos(obj, 221, 99);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "C");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdd7e0f), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_roomhumid_dashboard
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_roomhumid_dashboard = obj;
            lv_obj_set_pos(obj, 241, 99);
            lv_obj_set_size(obj, 56, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "60.65");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff008c8c), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_roomhumid_unit_dashboard_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_roomhumid_unit_dashboard_2 = obj;
            lv_obj_set_pos(obj, 298, 99);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "%");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff008c8c), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_info_header_dashboard
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_info_header_dashboard = obj;
            lv_obj_set_pos(obj, 163, 146);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "PTHM System");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_info_date_dashboard
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_info_date_dashboard = obj;
            lv_obj_set_pos(obj, 184, 180);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Date : ");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_info_time_dashboard
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_info_time_dashboard = obj;
            lv_obj_set_pos(obj, 183, 205);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Time : ");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_img_info_logo_dashboard
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pthm_img_info_logo_dashboard = obj;
            lv_obj_set_pos(obj, 142, 179);
            lv_obj_set_size(obj, 40, 40);
            lv_img_set_src(obj, &img_img_logo);
        }
        {
            // pthm_label_info_date_value_dashboard
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_info_date_value_dashboard = obj;
            lv_obj_set_pos(obj, 229, 180);
            lv_obj_set_size(obj, 82, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "16/02/2567");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_info_time_value_dashboard
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_info_time_value_dashboard = obj;
            lv_obj_set_pos(obj, 232, 205);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "15:06");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

void create_screen_heart_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.heart_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // pthm_panel_menu_2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pthm_panel_menu_2 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 40);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00b5e2), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_button_heart_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_heart_2 = obj;
            lv_obj_set_pos(obj, 85, 8);
            lv_obj_set_size(obj, 70, 25);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffdda518), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Heart");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_button_temp_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_temp_2 = obj;
            lv_obj_set_pos(obj, 165, 8);
            lv_obj_set_size(obj, 70, 25);
            lv_obj_add_event_cb(obj, action_event_handler_temp_page, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4a90e2), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Temp");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_button_room_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_room_2 = obj;
            lv_obj_set_pos(obj, 245, 8);
            lv_obj_set_size(obj, 70, 25);
            lv_obj_add_event_cb(obj, action_event_handler_room_page, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4a90e2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Room");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_button_dashboard_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_dashboard_2 = obj;
            lv_obj_set_pos(obj, 3, 8);
            lv_obj_set_size(obj, 75, 25);
            lv_obj_add_event_cb(obj, action_event_handler_main_page, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4a90e2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj2 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Dashboard");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_panel_heart
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pthm_panel_heart = obj;
            lv_obj_set_pos(obj, 7, 49);
            lv_obj_set_size(obj, 308, 184);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffb6b6b6), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_img_spo2_heartpage
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pthm_img_spo2_heartpage = obj;
            lv_obj_set_pos(obj, 28, 158);
            lv_obj_set_size(obj, 60, 60);
            lv_img_set_src(obj, &img_img_spo2_heartpage);
        }
        {
            // pthm_label_heartrate_heartpage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_heartrate_heartpage = obj;
            lv_obj_set_pos(obj, 120, 105);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "120");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfff70000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_heartrate_unit_heartpage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_heartrate_unit_heartpage = obj;
            lv_obj_set_pos(obj, 209, 106);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Bpm");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfff70000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_spo2_heartpage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_spo2_heartpage = obj;
            lv_obj_set_pos(obj, 117, 178);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "99.96");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfff70000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_spo2_unit_heartpage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_spo2_unit_heartpage = obj;
            lv_obj_set_pos(obj, 239, 178);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "%");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfff70000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_img_heartrate_heartpage
            lv_obj_t *obj = lv_animimg_create(parent_obj);
            objects.pthm_img_heartrate_heartpage = obj;
            lv_obj_set_pos(obj, 26, 90);
            lv_obj_set_size(obj, 60, 60);
            static const lv_image_dsc_t *images[2] = {
                &img_img_heartrate_heartpage_bg,
                &img_img_heartrate_heartpage_sm,
            };
            lv_animimg_set_src(obj, (const void **)images, 2);
            lv_animimg_set_duration(obj, 1000);
            lv_animimg_set_repeat_count(obj, LV_ANIM_REPEAT_INFINITE);
            lv_animimg_start(obj);
        }
        {
            // pthm_label_heart_header
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_heart_header = obj;
            lv_obj_set_pos(obj, 35, 58);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Heart & Blood Monitoring");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_heart_page();
}

void tick_screen_heart_page() {
}

void create_screen_temp_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.temp_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // pthm_panel_menu_temppage
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pthm_panel_menu_temppage = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 40);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00b5e2), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_button_heart_temppage
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_heart_temppage = obj;
            lv_obj_set_pos(obj, 85, 8);
            lv_obj_set_size(obj, 70, 25);
            lv_obj_add_event_cb(obj, action_event_handler_heart_page, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4a90e2), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj3 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Heart");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_button_temp_temppage
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_temp_temppage = obj;
            lv_obj_set_pos(obj, 165, 8);
            lv_obj_set_size(obj, 70, 25);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffdda518), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Temp");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_button_room_temppage
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_room_temppage = obj;
            lv_obj_set_pos(obj, 245, 8);
            lv_obj_set_size(obj, 70, 25);
            lv_obj_add_event_cb(obj, action_event_handler_room_page, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4a90e2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Room");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_button_dashboard_temppage
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_dashboard_temppage = obj;
            lv_obj_set_pos(obj, 3, 8);
            lv_obj_set_size(obj, 75, 25);
            lv_obj_add_event_cb(obj, action_event_handler_main_page, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4a90e2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj4 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Dashboard");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_panel_temp
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pthm_panel_temp = obj;
            lv_obj_set_pos(obj, 8, 45);
            lv_obj_set_size(obj, 308, 184);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffb6b6b6), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_arc_bodytemp_temppage
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.pthm_arc_bodytemp_temppage = obj;
            lv_obj_set_pos(obj, 27, 100);
            lv_obj_set_size(obj, 158, 139);
            lv_arc_set_range(obj, 28, 45);
            lv_arc_set_value(obj, 35.5);
            lv_arc_set_bg_start_angle(obj, 150);
            lv_arc_set_bg_end_angle(obj, 30);
            lv_obj_set_style_arc_width(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffb6b6b6), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 15, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff3cc905), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 15, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff44df07), LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_temp_header
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_temp_header = obj;
            lv_obj_set_pos(obj, 23, 59);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Body Temperature Monitoring");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_img_bodytemp_temppage
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pthm_img_bodytemp_temppage = obj;
            lv_obj_set_pos(obj, 63, 135);
            lv_obj_set_size(obj, 65, 65);
            lv_img_set_src(obj, &img_img_bodytemp_temppage);
        }
        {
            // pthm_label_bodytemp_temppage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_bodytemp_temppage = obj;
            lv_obj_set_pos(obj, 180, 131);
            lv_obj_set_size(obj, 91, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "35.5");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_bodytemp_unit_temppage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_bodytemp_unit_temppage = obj;
            lv_obj_set_pos(obj, 278, 131);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "C");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_bodytemp_min_temppage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_bodytemp_min_temppage = obj;
            lv_obj_set_pos(obj, 34, 204);
            lv_obj_set_size(obj, 35, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "28");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_bodytemp_max_temppage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_bodytemp_max_temppage = obj;
            lv_obj_set_pos(obj, 109, 204);
            lv_obj_set_size(obj, 35, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "45");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_temp_page();
}

void tick_screen_temp_page() {
}

void create_screen_room_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.room_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // pthm_panel_menu_roompage
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pthm_panel_menu_roompage = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 40);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00b5e2), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_button_heart_roompage
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_heart_roompage = obj;
            lv_obj_set_pos(obj, 85, 8);
            lv_obj_set_size(obj, 70, 25);
            lv_obj_add_event_cb(obj, action_event_handler_heart_page, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4a90e2), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Heart");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_button_temp_roompage
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_temp_roompage = obj;
            lv_obj_set_pos(obj, 165, 8);
            lv_obj_set_size(obj, 70, 25);
            lv_obj_add_event_cb(obj, action_event_handler_temp_page, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4a90e2), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Temp");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_button_ecg_roompage
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_ecg_roompage = obj;
            lv_obj_set_pos(obj, 245, 8);
            lv_obj_set_size(obj, 70, 25);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffdda518), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj5 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Room");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_button_dashboard_roompage
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pthm_button_dashboard_roompage = obj;
            lv_obj_set_pos(obj, 3, 8);
            lv_obj_set_size(obj, 75, 25);
            lv_obj_add_event_cb(obj, action_event_handler_main_page, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4a90e2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj6 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Dashboard");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // pthm_panel_room
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pthm_panel_room = obj;
            lv_obj_set_pos(obj, 7, 47);
            lv_obj_set_size(obj, 308, 184);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffb6b6b6), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_roomtemp_roompage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_roomtemp_roompage = obj;
            lv_obj_set_pos(obj, 104, 100);
            lv_obj_set_size(obj, 115, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "35.56");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdd7e0f), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_roomtemp_unit_roompage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_roomtemp_unit_roompage = obj;
            lv_obj_set_pos(obj, 250, 100);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "C");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdd7e0f), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_roomhumid_roompage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_roomhumid_roompage = obj;
            lv_obj_set_pos(obj, 114, 171);
            lv_obj_set_size(obj, 107, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "60.65");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff008c8c), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_roomhumid_unit_roompage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_roomhumid_unit_roompage = obj;
            lv_obj_set_pos(obj, 247, 172);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "%");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff008c8c), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_label_room_header
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pthm_label_room_header = obj;
            lv_obj_set_pos(obj, 20, 58);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Room Condition Monitoring");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pthm_img_roomtemp_roompage
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pthm_img_roomtemp_roompage = obj;
            lv_obj_set_pos(obj, 31, 86);
            lv_obj_set_size(obj, 60, 60);
            lv_img_set_src(obj, &img_img_roomtemp_roompage);
        }
        {
            // pthm_img_roomhumid_roompage
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pthm_img_roomhumid_roompage = obj;
            lv_obj_set_pos(obj, 26, 156);
            lv_obj_set_size(obj, 60, 60);
            lv_img_set_src(obj, &img_img_roomhumid_roompage);
        }
    }
    
    tick_screen_room_page();
}

void tick_screen_room_page() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_heart_page,
    tick_screen_temp_page,
    tick_screen_room_page,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_heart_page();
    create_screen_temp_page();
    create_screen_room_page();
}

#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

static void action_event_handler_main_page(lv_event_t * e);
static void action_event_handler_heart_page(lv_event_t * e);
static void action_event_handler_temp_page(lv_event_t * e);
static void action_event_handler_room_page(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/
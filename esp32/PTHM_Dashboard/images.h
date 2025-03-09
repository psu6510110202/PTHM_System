#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_img_heartrate;
extern const lv_img_dsc_t img_img_spo2;
extern const lv_img_dsc_t img_img_heartrate_sm;
extern const lv_img_dsc_t img_img_bodytemp;
extern const lv_img_dsc_t img_img_roomtemp;
extern const lv_img_dsc_t img_img_roomhumid;
extern const lv_img_dsc_t img_img_logo;
extern const lv_img_dsc_t img_img_heartrate_heartpage_bg;
extern const lv_img_dsc_t img_img_heartrate_heartpage_sm;
extern const lv_img_dsc_t img_img_spo2_heartpage;
extern const lv_img_dsc_t img_img_bodytemp_temppage;
extern const lv_img_dsc_t img_img_roomtemp_roompage;
extern const lv_img_dsc_t img_img_roomhumid_roompage;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[13];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/
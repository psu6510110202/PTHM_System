#include "images.h"

const ext_img_desc_t images[13] = {
    { "img_heartrate", &img_img_heartrate },
    { "img_spo2", &img_img_spo2 },
    { "img_heartrate_sm", &img_img_heartrate_sm },
    { "img_bodytemp", &img_img_bodytemp },
    { "img_roomtemp", &img_img_roomtemp },
    { "img_roomhumid", &img_img_roomhumid },
    { "img_logo", &img_img_logo },
    { "img_heartrate_heartpage_bg", &img_img_heartrate_heartpage_bg },
    { "img_heartrate_heartpage_sm", &img_img_heartrate_heartpage_sm },
    { "img_spo2_heartpage", &img_img_spo2_heartpage },
    { "img_bodytemp_temppage", &img_img_bodytemp_temppage },
    { "img_roomtemp_roompage", &img_img_roomtemp_roompage },
    { "img_roomhumid_roompage", &img_img_roomhumid_roompage },
};

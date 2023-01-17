// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.2.0
// PROJECT: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

    #include "lvgl.h"

extern lv_obj_t *ui_Splash_Screen;
void ui_event_Splash_Screen_Title( lv_event_t * e);
extern lv_obj_t *ui_Splash_Screen_Title;
extern lv_obj_t *ui_Splash_Screen_Text;
extern lv_obj_t *ui_OTA_Panel;
extern lv_obj_t *ui_OTA_Screen_Title;
extern lv_obj_t *ui_OTA_Status;
extern lv_obj_t *ui_OTA_Spinner;
extern lv_obj_t *ui_Main_Screen;
extern lv_obj_t *ui_Counter_Display;
void ui_event_Counter_Button( lv_event_t * e);
extern lv_obj_t *ui_Counter_Button;
extern lv_obj_t *ui_Counter_Button_Label;

void splashScreenTapped_cb(lv_event_t * e);
void counterButtonClicked_cb(lv_event_t * e);





void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

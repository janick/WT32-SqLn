// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.2.0
// PROJECT: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_Splash_Screen;
void ui_event_Splash_Screen_Title( lv_event_t * e);
lv_obj_t *ui_Splash_Screen_Title;
lv_obj_t *ui_Splash_Screen_Text;
lv_obj_t *ui_OTA_Panel;
lv_obj_t *ui_OTA_Screen_Title;
lv_obj_t *ui_OTA_Status;
lv_obj_t *ui_OTA_Spinner;
lv_obj_t *ui_Main_Screen;
lv_obj_t *ui_Counter_Display;
void ui_event_Counter_Button( lv_event_t * e);
lv_obj_t *ui_Counter_Button;
lv_obj_t *ui_Counter_Button_Label;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Splash_Screen_Title( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      splashScreenTapped_cb( e );
}
}
void ui_event_Counter_Button( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      counterButtonClicked_cb( e );
}
}

///////////////////// SCREENS ////////////////////
void ui_Splash_Screen_screen_init(void)
{
ui_Splash_Screen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Splash_Screen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Splash_Screen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Splash_Screen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Splash_Screen_Title = lv_label_create(ui_Splash_Screen);
lv_obj_set_width( ui_Splash_Screen_Title, lv_pct(100));
lv_obj_set_height( ui_Splash_Screen_Title, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Splash_Screen_Title, 0 );
lv_obj_set_y( ui_Splash_Screen_Title, -180 );
lv_obj_set_align( ui_Splash_Screen_Title, LV_ALIGN_CENTER );
lv_label_set_long_mode(ui_Splash_Screen_Title,LV_LABEL_LONG_CLIP);
lv_label_set_text(ui_Splash_Screen_Title,"Project Title");
lv_obj_add_flag( ui_Splash_Screen_Title, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_clear_flag( ui_Splash_Screen_Title, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_text_align(ui_Splash_Screen_Title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Splash_Screen_Title, &lv_font_montserrat_38, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Splash_Screen_Text = lv_label_create(ui_Splash_Screen);
lv_obj_set_height( ui_Splash_Screen_Text, 350);
lv_obj_set_width( ui_Splash_Screen_Text, lv_pct(90));
lv_obj_set_x( ui_Splash_Screen_Text, 0 );
lv_obj_set_y( ui_Splash_Screen_Text, 40 );
lv_obj_set_align( ui_Splash_Screen_Text, LV_ALIGN_CENTER );
lv_label_set_text(ui_Splash_Screen_Text,"Device Info");

ui_OTA_Panel = lv_obj_create(ui_Splash_Screen);
lv_obj_set_width( ui_OTA_Panel, lv_pct(100));
lv_obj_set_height( ui_OTA_Panel, lv_pct(100));
lv_obj_set_align( ui_OTA_Panel, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_OTA_Panel, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_clear_flag( ui_OTA_Panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_bg_color(ui_OTA_Panel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_OTA_Panel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_OTA_Panel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_OTA_Panel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_OTA_Screen_Title = lv_label_create(ui_OTA_Panel);
lv_obj_set_width( ui_OTA_Screen_Title, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_OTA_Screen_Title, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_OTA_Screen_Title, 20 );
lv_obj_set_y( ui_OTA_Screen_Title, 20 );
lv_label_set_text(ui_OTA_Screen_Title,"OTA");
lv_obj_set_style_text_font(ui_OTA_Screen_Title, &lv_font_montserrat_38, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_OTA_Status = lv_label_create(ui_OTA_Panel);
lv_obj_set_height( ui_OTA_Status, 350);
lv_obj_set_width( ui_OTA_Status, lv_pct(90));
lv_obj_set_x( ui_OTA_Status, 0 );
lv_obj_set_y( ui_OTA_Status, 30 );
lv_obj_set_align( ui_OTA_Status, LV_ALIGN_CENTER );
lv_label_set_text(ui_OTA_Status,"OTA Status...");

ui_OTA_Spinner = lv_spinner_create(ui_OTA_Panel,1000,90);
lv_obj_set_width( ui_OTA_Spinner, 80);
lv_obj_set_height( ui_OTA_Spinner, 80);
lv_obj_set_x( ui_OTA_Spinner, 0 );
lv_obj_set_y( ui_OTA_Spinner, 120 );
lv_obj_set_align( ui_OTA_Spinner, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_OTA_Spinner, LV_OBJ_FLAG_CLICKABLE );    /// Flags

lv_obj_add_event_cb(ui_Splash_Screen_Title, ui_event_Splash_Screen_Title, LV_EVENT_ALL, NULL);

}
void ui_Main_Screen_screen_init(void)
{
ui_Main_Screen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Main_Screen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Main_Screen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Main_Screen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Counter_Display = lv_label_create(ui_Main_Screen);
lv_obj_set_width( ui_Counter_Display, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Counter_Display, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Counter_Display, 0 );
lv_obj_set_y( ui_Counter_Display, -100 );
lv_obj_set_align( ui_Counter_Display, LV_ALIGN_CENTER );
lv_label_set_text(ui_Counter_Display,"0");
lv_obj_set_style_text_font(ui_Counter_Display, &lv_font_montserrat_38, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Counter_Button = lv_btn_create(ui_Main_Screen);
lv_obj_set_width( ui_Counter_Button, 150);
lv_obj_set_height( ui_Counter_Button, 60);
lv_obj_set_x( ui_Counter_Button, 0 );
lv_obj_set_y( ui_Counter_Button, 30 );
lv_obj_set_align( ui_Counter_Button, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Counter_Button, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Counter_Button, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Counter_Button, 20, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Counter_Button, lv_color_hex(0x7F7F7F), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Counter_Button, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Counter_Button_Label = lv_label_create(ui_Main_Screen);
lv_obj_set_width( ui_Counter_Button_Label, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Counter_Button_Label, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Counter_Button_Label, 0 );
lv_obj_set_y( ui_Counter_Button_Label, 30 );
lv_obj_set_align( ui_Counter_Button_Label, LV_ALIGN_CENTER );
lv_label_set_text(ui_Counter_Button_Label,"Click me!");
lv_obj_set_style_text_color(ui_Counter_Button_Label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Counter_Button_Label, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Counter_Button_Label, &lv_font_montserrat_28, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_Counter_Button, ui_event_Counter_Button, LV_EVENT_ALL, NULL);

}

void ui_init( void )
{
lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_Splash_Screen_screen_init();
ui_Main_Screen_screen_init();
lv_disp_load_scr( ui_Splash_Screen);
}




void splashScreenTapped_cb(lv_event_t * e)
{
    static int tapCount = 0;
    
    if (HELPER::OTA::taskHandle != NULL) return;

    if (++tapCount < 5) return;

    //
    // The OTA "screen" is a hidden panel over the splash screen
    // to minimize the number of screens used in Squareline Studio
    //
    {
        lvglLock lock;
        
        HELPER::UI::showOTASpinner(false);
        lv_obj_clear_flag(ui_OTA_Panel, LV_OBJ_FLAG_HIDDEN);
        
        HELPER::UI::textAppend = HELPER::UI::textbuf;
        *HELPER::UI::textAppend = '\0';
        
        HELPER::UI::appendOTAstatus("Starting OTA...\n");
    }
    
    xTaskCreate(&HELPER::OTA::task, "OTA::task", 8192, NULL, 5, &HELPER::OTA::taskHandle);
}


//
// Main Screen Helpers
//

void counterButtonClicked_cb(lv_event_t * e)
{
    static int clickCount = 0;
    char image[16];
    
    lvglLock lock;
    lv_label_set_text(ui_Counter_Display, itoa(++clickCount, image, 10));
}


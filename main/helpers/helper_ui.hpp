/*
MIT License

Copyright (c) 2023  Janick Bergeron  <janick@bergeron.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include "esp_log.h"
#include "ui.h"


namespace HELPER {

namespace OTA {
    void task(void*);
    extern TaskHandle_t taskHandle;
};


namespace UI {

//
// OTA Screen Helpers
//

static char  textbuf[4096];
static char* textAppend = textbuf;


void appendOTAstatus(const char* text)
{
    int len       = strlen(text);
    int remaining = sizeof(textbuf) - (textAppend - textbuf) - 1;
    
    if (len > remaining) len = remaining;
    if (len <= 0) return;

    lvglLock lock;
    
    strncpy(textAppend, text, len+1);
    textAppend += len;

    lv_label_set_text_static(ui_OTA_Status, textbuf);
}


void showOTASpinner(bool show)
{
    lvglLock lock;

    if (show) {
        lv_obj_clear_flag(ui_OTA_Spinner, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(ui_OTA_Spinner, LV_OBJ_FLAG_HIDDEN);
    }
}



void splashScreenTapped_cb(lv_event_t * e)
{
    static int tapCount = 0;
    
    if (OTA::taskHandle != NULL) return;

    if (++tapCount < 5) return;

    //
    // The OTA "screen" is a hidden panel over the splash screen
    // to minimize the number of screens used in Squareline Studio
    //
    {
        lvglLock lock;
        
        showOTASpinner(false);
        lv_obj_clear_flag(ui_OTA_Panel, LV_OBJ_FLAG_HIDDEN);
        
        textAppend = textbuf;
        *textAppend = '\0';
        
        appendOTAstatus("Starting OTA...\n");
    }
    
    xTaskCreate(&OTA::task, "OTA::task", 8192, NULL, 5, &OTA::taskHandle);
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

};
};

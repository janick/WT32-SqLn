/*
MIT License

Copyright (c) 2022 Sukesh Ashok Kumar
Copyright (c) 2023 Janick Bergeron  <janick@bergeron.com>

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

#ifndef TUX_CONF_H
#define TUX_CONF_H

#include "esp_log.h"
#include "nvs_flash.h"

#include <cmath>
#include <inttypes.h>
#include <string>
#include <esp_chip_info.h>
#include <esp_event.h>
#include <esp_flash.h>
#include <esp_ota_ops.h>
#include <soc/rtc.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <freertos/FreeRTOS.h>

using namespace std ;

//#include "conf_WT32SCO1.h"              // WT32-SC01 (ESP32)
#include "conf_WT32SCO1-Plus.h"         
//#include "conf_Makerfabs_S3_STFT.h" 
//#include "conf_Makerfabs_S3_PTFT.h"    
#undef SD_SUPPORTED
/********************************************************/

#include "helper_display.hpp"
#include "helper_ui.hpp"
#include "helper_ota.hpp"


/* SD Card support */
#if defined(SD_SUPPORTED)
        // Shared SPI Bus with Display
    #if defined(WT32_SC01) //|| defined(MAKERFAB_ESP32S3_SPI)
        #include "helper_storage_shared.hpp"
    #else
        // Display and SD card is not on same SPI bus
        #include "helper_storage.hpp"
    #endif
#endif

// UI design
#include "ui.h"


static string device_info();

static bool is_dark_theme = true;

char devinfo_data[300] = {0};   // Device info

#endif // TUX_CONF_H

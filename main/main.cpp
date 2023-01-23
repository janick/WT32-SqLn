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

static const char *TAG = "WT32-SqLn";

#include "main.hpp"

extern "C" void app_main(void)
{
    esp_log_level_set(TAG, ESP_LOG_DEBUG);      // enable DEBUG logs for this App
    //esp_log_level_set("SettingsConfig", ESP_LOG_DEBUG);    
    esp_log_level_set("wifi", ESP_LOG_WARN);    // enable WARN logs from WiFi stack

    // Print device info
    ESP_LOGE(TAG,"\n%s",device_info().c_str());

    //Initialize NVS
    esp_err_t err = nvs_flash_init();

    // NVS partition contains new data format or unable to access
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err); 

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

#ifdef SD_SUPPORTED
    // Initializing SDSPI 
    if (init_sdspi() == ESP_OK) // SD SPI
    {
        is_sdcard_enabled = true;
    }
#endif

    lcd.init();         // Initialize LovyanGFX
    lcd.initDMA();      // Init DMA
    lv_init();          // Initialize lvgl

    if (lv_display_init() != ESP_OK) // Configure LVGL
    {
        ESP_LOGE(TAG, "LVGL setup failed!!!");
    }

    {
        lvglLock lock;
        
        ui_init();
        lv_label_set_text(ui_Splash_Screen_Title, TAG);
        lv_label_set_text(ui_Splash_Screen_Text, device_info().c_str());
        lv_obj_set_style_text_font(ui_Splash_Screen_Text, &lv_font_unscii_8, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_scr_load(ui_Splash_Screen);
    }

    // Switch to the main application if OTA has not been started
    vTaskDelay(pdMS_TO_TICKS(5000));
    if (otaTaskHandle == NULL) {
        lvglLock lock;

        lv_scr_load(ui_Main_Screen);
    }
    
#ifdef SD_SUPPORTED
    // Icon status color update
    lv_msg_send(MSG_SDCARD_STATUS,&is_sdcard_enabled);
#endif

    ESP_LOGI(TAG, "[APP] Free memory: %" PRIu32 " bytes", esp_get_free_heap_size());
}

static string device_info()
{
    std::string s_chip_info = "";

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);

    // CPU Speed - 80Mhz / 160 Mhz / 240Mhz
    rtc_cpu_freq_config_t conf;
    rtc_clk_cpu_freq_get_config(&conf);

    multi_heap_info_t info;    
	heap_caps_get_info(&info, MALLOC_CAP_SPIRAM);
    float psramsize = (info.total_free_bytes + info.total_allocated_bytes) / (1024.0 * 1024.0);

    const esp_partition_t *running = esp_ota_get_running_partition();
    esp_app_desc_t running_app_info;
    
    if (esp_ota_get_partition_description(running, &running_app_info) == ESP_OK) {
        s_chip_info += fmt::format("Project Name : {}\n",running_app_info.project_name);
        s_chip_info += fmt::format("Firmware Ver : {}\n",running_app_info.version);
    }
    s_chip_info += fmt::format("IDF Version  : {}\n\n",esp_get_idf_version());

    s_chip_info += fmt::format("Controller   : {} Rev.{}\n",CONFIG_IDF_TARGET,chip_info.revision);  
    //s_chip_info += fmt::format("\nModel         : {}",chip_info.model); // esp_chip_model_t type
    s_chip_info += fmt::format("CPU Cores    : {}\n", (chip_info.cores==2)? "Dual Core" : "Single Core");
    s_chip_info += fmt::format("CPU Speed    : {}Mhz\n",conf.freq_mhz);
    if(esp_flash_get_size(NULL, &flash_size) == ESP_OK) {
    s_chip_info += fmt::format("Flash Size   : {}MB {}\n",flash_size / (1024 * 1024),
                                            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "[embedded]" : "[external]");
    }
    s_chip_info += fmt::format("PSRAM Size   : {}MB {}\n",static_cast<int>(round(psramsize)),
                                            (chip_info.features & CHIP_FEATURE_EMB_PSRAM) ? "[embedded]" : "[external]");

    s_chip_info += fmt::format("Connectivity : {}{}{}\n",(chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "2.4GHz WIFI" : "NA",
                                                    (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
                                                    (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
    //s_chip_info += fmt::format("\nIEEE 802.15.4 : {}",string((chip_info.features & CHIP_FEATURE_IEEE802154) ? "YES" : "NA"));

    //ESP_LOGE(TAG,"\n%s",device_info().c_str());
    return s_chip_info;
}

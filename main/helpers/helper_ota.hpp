/*
MIT License

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


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "string.h"

#include "nvs.h"
#include "nvs_flash.h"
#include <sys/socket.h>
#include "esp_wifi.h"

#include "secrets.h"

#define HASH_LEN 32

extern const uint8_t* server_cert_pem_start asm("_binary_ca_cert_pem_start");
extern const uint8_t* server_cert_pem_end   asm("_binary_ca_cert_pem_end");


esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id) {
    case HTTP_EVENT_ERROR:
        ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
        break;
    case HTTP_EVENT_HEADER_SENT:
        ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
        break;
    case HTTP_EVENT_ON_HEADER:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
        break;
    case HTTP_EVENT_ON_DATA:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_DISCONNECTED");
        break;
    case HTTP_EVENT_REDIRECT:
        ESP_LOGD(TAG, "HTTP_EVENT_REDIRECT");
        break;
    }
    return ESP_OK;
}


static esp_netif_t *s_sta_netif = NULL;
static SemaphoreHandle_t s_semph_get_ip_addrs = xSemaphoreCreateBinary();

static int s_retry_num = 0;
#define WIFI_CONNECT_MAX_RETRY 10

static void handler_on_wifi_disconnect(void *arg, esp_event_base_t event_base,
                                               int32_t event_id, void *event_data)
{
    s_retry_num++;
    if (s_retry_num > WIFI_CONNECT_MAX_RETRY) {
        ESP_LOGI(TAG, "WiFi Connect failed %d times, stop reconnect.", s_retry_num);
        xSemaphoreGive(s_semph_get_ip_addrs);
        return;
    }
    ESP_LOGI(TAG, "Wi-Fi disconnected, trying to reconnect...");
    esp_err_t err = esp_wifi_connect();
    if (err == ESP_ERR_WIFI_NOT_STARTED) {
        return;
    }
    ESP_ERROR_CHECK(err);
}

static void handler_on_wifi_connect(void *esp_netif, esp_event_base_t event_base,
                                            int32_t event_id, void *event_data)
{
    ESP_LOGI(TAG, "Connected Event.");
}

static void handler_on_sta_got_ip(void *arg, esp_event_base_t event_base,
                                          int32_t event_id, void *event_data)
{
    ESP_LOGI(TAG, "Got IP address...");
    
    s_retry_num = 0;
    ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
    ESP_LOGI(TAG, "Got IPv4 event: Interface \"%s\" address: " IPSTR, esp_netif_get_desc(event->esp_netif), IP2STR(&event->ip_info.ip));
    xSemaphoreGive(s_semph_get_ip_addrs);
}


void wifi_start(void)
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_netif_inherent_config_t esp_netif_config = ESP_NETIF_INHERENT_DEFAULT_WIFI_STA();
    // Warning: the interface desc is used in tests to capture actual connection details (IP, gw, mask)
    esp_netif_config.if_desc = "WT32-RR";
    esp_netif_config.route_prio = 128;
    s_sta_netif = esp_netif_create_wifi(WIFI_IF_STA, &esp_netif_config);
    esp_wifi_set_default_wifi_sta_handlers();

    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    esp_wifi_set_ps(WIFI_PS_NONE);
}


void wifi_stop(void)
{
    esp_err_t err = esp_wifi_stop();
    if (err == ESP_ERR_WIFI_NOT_INIT) {
        return;
    }
    ESP_ERROR_CHECK(err);
    ESP_ERROR_CHECK(esp_wifi_deinit());
    ESP_ERROR_CHECK(esp_wifi_clear_default_wifi_driver_and_handlers(s_sta_netif));
    esp_netif_destroy(s_sta_netif);
    s_sta_netif = NULL;
}


void wifi_shutdown(void)
{
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &handler_on_wifi_disconnect));
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &handler_on_sta_got_ip));
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED, &handler_on_wifi_connect));

    xSemaphoreGive(s_semph_get_ip_addrs);

    esp_wifi_disconnect();
    wifi_stop();
}

esp_err_t wifi_connect(void)
{
    ESP_LOGI(TAG, "Start connect.");
    appendOTAstatus("Enabling WiFi...\n");
    wifi_start();

    wifi_config_t wifi_config;
    bzero(&wifi_config, sizeof(wifi_config));
    strncpy((char*) wifi_config.sta.ssid,     wifiCredentials.ssid,   sizeof(wifi_config.sta.ssid));
    strncpy((char*) wifi_config.sta.password, wifiCredentials.passwd, sizeof(wifi_config.sta.password));
    wifi_config.sta.scan_method = WIFI_FAST_SCAN;
    
    appendOTAstatus("Connecting to '");
    appendOTAstatus((char*) wifi_config.sta.ssid);
    appendOTAstatus("'...\n");

    s_retry_num = 0;
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &handler_on_wifi_disconnect, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &handler_on_sta_got_ip, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED, &handler_on_wifi_connect, s_sta_netif));

    ESP_LOGI(TAG, "Connecting to '%s' using '%s'...", wifi_config.sta.ssid, wifi_config.sta.password);
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    esp_err_t ret = esp_wifi_connect();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "WiFi connect failed! ret:%x", ret);
        return ret;
    }
    ESP_LOGI(TAG, "Waiting for IP(s)");
    xSemaphoreTake(s_semph_get_ip_addrs, portMAX_DELAY);
    if (s_retry_num > WIFI_CONNECT_MAX_RETRY) {
        return ESP_FAIL;
    }

    esp_netif_ip_info_t info;
    ESP_ERROR_CHECK(esp_netif_get_ip_info(s_sta_netif, &info));
    ESP_LOGI(TAG, "Wifi connected: " IPSTR, IP2STR(&info.ip));
    appendOTAstatus(fmt::format("Connected as {}.{}.{}.{}\n", IP2STR(&info.ip)).c_str());
    
    return ESP_OK;
}


void ota_task(void *pvParameter)
{
    esp_log_level_set("*", ESP_LOG_VERBOSE);
    
    ESP_LOGI(TAG, "Starting OTA task...");

    ESP_ERROR_CHECK(wifi_connect());

    std::string url = fmt::format("https://{}:{}/build/{}.bin", httpsCredentials.addr, httpsCredentials.port, TAG);

    esp_http_client_config_t config;
    bzero(&config, sizeof(config));
    config.url               = url.c_str();
    config.cert_pem          = httpsCredentials.cert;  // Why doesn't this work?? (char *) server_cert_pem_start;
    config.event_handler     = _http_event_handler;
    config.keep_alive_enable = true;

    //    config.skip_cert_common_name_check = true;

    esp_https_ota_config_t ota_config = {
        .http_config = &config,
    };

    
    ESP_LOGI(TAG, "Fetching update from %s", config.url);
    appendOTAstatus(fmt::format("Updating using '{}'...\n\nPlease wait ~2 mins.\n", config.url).c_str());

    showOTASpinner(true);

    esp_err_t ret = esp_https_ota(&ota_config);

    showOTASpinner(false);

    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "OTA Succeed, Rebooting...");
        appendOTAstatus("\nOTA OK!\n");
        vTaskDelay(pdMS_TO_TICKS(500));
        esp_restart();
    } else {
        appendOTAstatus("\n** OTA FAILED! **\n");
        ESP_LOGE(TAG, "Firmware upgrade failed");
        while (1) vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    otaTaskHandle = NULL;
    
    vTaskDelete(NULL);
}

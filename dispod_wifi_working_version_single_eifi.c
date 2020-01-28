#include "esp_wifi.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_log.h"

#include "dispod_wifi.h"

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
#include "freertos/event_groups.h"

static const char* TAG = "DISPOD_WIFI";


// WiFi event handler -> TODO extend to overall event handler or take new one?
static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "got ip:%s",
            ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        wifi_retry_num = 0;
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        if (wifi_retry_num < DISPOD_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            xEventGroupClearBits(wifi_event_group, WIFI_CONNECTED_BIT);
            wifi_retry_num++;
            ESP_LOGI(TAG,"retry to connect to the AP");
        }
        ESP_LOGI(TAG,"connect to the AP fail\n");
        break;
    default:
        break;
    }
    return ESP_OK;
}


void initialize_wifi(void)
{
    wifi_event_group = xEventGroupCreate();

    tcpip_adapter_init();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );

    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = DISPOD_ESP_WIFI_SSID,
            .password = DISPOD_ESP_WIFI_PASS,
        },
    };

    ESP_LOGI(TAG, "Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    ESP_LOGI(TAG, "connect to ap SSID:%s password:%s",
             wifi_config.sta.ssid, wifi_config.sta.password);
}


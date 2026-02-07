#include "wifi_manager.h"
#include <string.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "lwip_nat.h"


#define MAIN_WIFI_SSID  "Lily's Router"
#define MAIN_WIFI_PASS  "Lily@2025"

#define AP_WIFI_SSID    "ESP32_Repeater"
#define AP_WIFI_PASS    "12345678"
#define MAX_STA_CONN    5

static const char *TAG = "wifi_manager";

void wifi_manager_start(void)
{
    esp_netif_init();
    esp_event_loop_create_default();

    esp_netif_create_default_wifi_sta();
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    wifi_config_t sta_config = {
        .sta = {
            .ssid = MAIN_WIFI_SSID,
            .password = MAIN_WIFI_PASS,
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
        }
    };

    wifi_config_t ap_config = {
        .ap = {
            .ssid = AP_WIFI_SSID,
            .ssid_len = strlen(AP_WIFI_SSID),
            .password = AP_WIFI_PASS,
            .max_connection = MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        }
    };

    if (strlen(AP_WIFI_PASS) == 0) {
        ap_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    esp_wifi_set_mode(WIFI_MODE_APSTA);
    esp_wifi_set_config(WIFI_IF_STA, &sta_config);
    esp_wifi_set_config(WIFI_IF_AP, &ap_config);

    esp_wifi_start();
    esp_wifi_start();
    esp_wifi_connect();
    /* Enable NAT */
    lwip_nat_init();

    esp_wifi_connect();

    ESP_LOGI(TAG, "Wi-Fi Extender started (AP + STA)");
}

int wifi_manager_get_rssi(void)
{
    wifi_ap_record_t ap;
    if (esp_wifi_sta_get_ap_info(&ap) == ESP_OK) {
        return ap.rssi;
    }
    return -100;
}


int wifi_manager_get_client_count(void)
{
    return esp_wifi_ap_get_sta_list(NULL) == ESP_OK
           ? esp_wifi_ap_get_sta_list(NULL)
           : 0;
}

//
// Created by josemar on 15/12/2025.
//

#include "platform/wifi_esp32.h"

#include <string.h>
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

static const char *TAG = "wifi_esp32";

static wifi_status_cb_t s_cb = NULL;
static void *s_user = NULL;
static int s_retry = 0;

static void notify(WifiStatus st) {
    if (s_cb) s_cb(st, s_user);
}

static void handler(void *arg, esp_event_base_t base, int32_t id, void *data) {
    (void) arg;

    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_START) {
        ESP_LOGI(TAG, "STA_START -> connect");
        notify(WIFI_STATUS_CONNECTING);
        esp_wifi_connect();
        return;
    }

    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGW(TAG, "DISCONNECTED");
        notify(WIFI_STATUS_DISCONNECTED);

        if (s_retry < 10) {
            s_retry++;
            esp_wifi_connect();
        } else {
            notify(WIFI_STATUS_FAILED);
        }
        return;
    }

    if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *e = (ip_event_got_ip_t *) data;
        ESP_LOGI(TAG, "GOT_IP: " IPSTR, IP2STR(&e->ip_info.ip));
        s_retry = 0;
        notify(WIFI_STATUS_CONNECTED);
        return;
    }
}

bool platform_wifi_start_sta(const char *ssid, const char *pass,
                             wifi_status_cb_t cb, void *user) {
    s_cb = cb;
    s_user = user;

    // NVS é necessário pro Wi-Fi
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    if (err != ESP_OK) return false;

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &handler, NULL));

    wifi_config_t w = {0};
    strncpy((char *) w.sta.ssid, ssid, sizeof(w.sta.ssid));
    strncpy((char *) w.sta.password, pass, sizeof(w.sta.password));
    w.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;
    w.sta.pmf_cfg.capable = true;
    w.sta.pmf_cfg.required = false;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &w));
    ESP_ERROR_CHECK(esp_wifi_start());

    notify(WIFI_STATUS_CONNECTING);
    return true;
}

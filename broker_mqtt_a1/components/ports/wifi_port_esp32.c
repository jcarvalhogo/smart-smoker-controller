//
// Created by josemar on 15/12/2025.
//
#include "ports/wifi_port.h"
#include "platform/wifi_esp32.h"

static bool start_sta_impl(const char *ssid, const char *pass, wifi_status_cb_t cb, void *user) {
    return platform_wifi_start_sta(ssid, pass, cb, user);
}

WifiPort wifi_port(void) {
    return (WifiPort){
        .start_sta = start_sta_impl,
    };
}

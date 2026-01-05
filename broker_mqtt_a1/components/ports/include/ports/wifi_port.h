//
// Created by josemar on 15/12/2025.
//

#ifndef BROKER_MQTT_A1_WIFI_PORT_H
#define BROKER_MQTT_A1_WIFI_PORT_H
#pragma once

typedef enum {
    WIFI_STATUS_CONNECTING = 0,
    WIFI_STATUS_CONNECTED,
    WIFI_STATUS_DISCONNECTED,
    WIFI_STATUS_FAILED,
} WifiStatus;

typedef void (*wifi_status_cb_t)(WifiStatus st, void *user);

typedef struct {
    bool (*start_sta)(const char *ssid, const char *pass, wifi_status_cb_t cb, void *user);
} WifiPort;

WifiPort wifi_port(void);

#endif //BROKER_MQTT_A1_WIFI_PORT_H
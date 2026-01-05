//
// Created by josemar on 15/12/2025.
//

#ifndef BROKER_MQTT_A1_APP_WIFI_LED_H
#define BROKER_MQTT_A1_APP_WIFI_LED_H
#pragma once
#include <stdint.h>

void app_wifi_led_start(const char *ssid, const char *pass, uint32_t led_gpio);

#endif //BROKER_MQTT_A1_APP_WIFI_LED_H
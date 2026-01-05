//
// Created by josemar on 15/12/2025.
//
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "app/app_wifi_led.h"
#include "app/app_mqtt.h"
#include "app/app_dht22.h"
#include "app/app_air_intake.h"
#include "app/app_valve.h"

#define WIFI_SSID "CARVALHO"
#define WIFI_PASS "15935700"
#define LED_GPIO  2
// #define MQTT_BROKER_URI "mqtt://192.168.3.3:1883"
#define MQTT_BROKER_URI "mqtt://192.168.3.3:1883"

void app_main(void) {
    app_wifi_led_start(WIFI_SSID, WIFI_PASS, LED_GPIO);
    app_mqtt_start(MQTT_BROKER_URI);
    app_dht22_start();
    app_air_intake_init();
    app_valve_init();

    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

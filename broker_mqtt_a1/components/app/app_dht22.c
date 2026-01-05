//
// Created by josemar on 03/01/2026.
//

#include "app/app_dht22.h"
#include "app/app_mqtt.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <stdio.h>

#include "dht.h"

static const char *TAG = "app_dht22";

#define DHT_GPIO        GPIO_NUM_4
#define DHT_TYPE        DHT_TYPE_AM2301 // DHT22 == AM2301
#define READ_PERIOD_MS  2000            // recommended minimum: 2s

// publish topics (relative -> JC_GO/<topic>)
#define TEMPERATURE_TOPIC "temperature"
#define HUMIDITY_TOPIC    "humidity"

static void vDht22Task(void *pvParameters) {
    (void) pvParameters;

    // initial delay (sensor stabilization)
    vTaskDelay(pdMS_TO_TICKS(READ_PERIOD_MS));

    for (;;) {
        float humidity = 0.0f;
        float temperature = 0.0f;

        esp_err_t err = dht_read_float_data(
            DHT_TYPE,
            DHT_GPIO,
            &humidity,
            &temperature
        );

        if (err == ESP_OK) {
            ESP_LOGI(
                TAG,
                "Temperature: %.1f C | Humidity: %.1f %%",
                temperature,
                humidity
            );

            if (app_mqtt_is_ready()) {
                char temp_json[64];
                char hum_json[64];

                // JSON payloads (separate topics)
                snprintf(
                    temp_json,
                    sizeof(temp_json),
                    "{\"temperature\":%.1f}",
                    temperature
                );

                snprintf(
                    hum_json,
                    sizeof(hum_json),
                    "{\"humidity\":%.1f}",
                    humidity
                );

                // QoS 1, retain false
                app_mqtt_publish(TEMPERATURE_TOPIC, temp_json, 1, false);
                app_mqtt_publish(HUMIDITY_TOPIC, hum_json, 1, false);
            } else {
                ESP_LOGW(TAG, "MQTT not ready, skipping publish");
            }
        } else {
            ESP_LOGW(
                TAG,
                "DHT22 read error: %s",
                esp_err_to_name(err)
            );
        }

        vTaskDelay(pdMS_TO_TICKS(READ_PERIOD_MS));
    }
}

void app_dht22_start(void) {
    xTaskCreate(
        vDht22Task,
        "DHT22_Task",
        4096, // safe stack for DHT
        NULL,
        5, // medium priority
        NULL
    );
}
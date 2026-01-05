//
// Created by josemar on 03/01/2026.
//

#include "app/app_air_intake.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "platform/servo_esp32.h"
#include "domain/servo_domain.h"

#include "esp_log.h"

static const char *TAG = "app_air_intake";

#ifndef AIR_INTAKE_GPIO
#define AIR_INTAKE_GPIO 18
#endif

#define AIR_INTAKE_QUEUE_LEN 8
#define AIR_INTAKE_TASK_STACK 3072
#define AIR_INTAKE_TASK_PRIO 6

static QueueHandle_t s_q = NULL;
static ServoPort s_servo;

static void air_intake_task(void *arg) {
    (void) arg;

    ServoPulseRange range = {
        .min_pulse_us = 500,
        .max_pulse_us = 2400,
    };

    uint8_t opening = 90; // neutral / default

    for (;;) {
        if (xQueueReceive(s_q, &opening, portMAX_DELAY) == pdTRUE) {
            uint32_t pulse = servo_domain_angle_to_pulse_us(opening, range);
            bool ok = s_servo.set_pulse_us(pulse);

            ESP_LOGI(
                TAG,
                "opening=%u pulse=%luus ok=%d",
                opening,
                (unsigned long)pulse,
                (int)ok
            );
        }
    }
}

bool app_air_intake_init(void) {
    // idempotent init (avoid creating resources twice)
    if (s_q) {
        ESP_LOGW(TAG, "air intake already initialized");
        return true;
    }

    s_servo = platform_servo_port();

    ServoPwmConfig cfg = {
        .gpio_num = AIR_INTAKE_GPIO,
        .freq_hz = 50,
        .duty_res_bits = 16,
        .min_pulse_us = 500,
        .max_pulse_us = 2400,
    };

    if (!s_servo.init(&cfg)) {
        ESP_LOGE(TAG, "air intake actuator init failed");
        return false;
    }

    s_q = xQueueCreate(AIR_INTAKE_QUEUE_LEN, sizeof(uint8_t));
    if (!s_q) {
        ESP_LOGE(TAG, "xQueueCreate failed");
        return false;
    }

    if (xTaskCreate(
            air_intake_task,
            "air_intake_task",
            AIR_INTAKE_TASK_STACK,
            NULL,
            AIR_INTAKE_TASK_PRIO,
            NULL
        ) != pdPASS) {
        ESP_LOGE(TAG, "xTaskCreate failed");
        return false;
    }

    // default opening (safe)
    (void) app_air_intake_set_position(90);
    ESP_LOGI(TAG, "air intake initialized");
    return true;
}

bool app_air_intake_set_position(uint8_t position) {
    if (!s_q) return false;

    // position is mapped to servo angle domain (0..180)
    if (position > 180) position = 180;

    return xQueueSend(s_q, &position, 0) == pdTRUE;
}

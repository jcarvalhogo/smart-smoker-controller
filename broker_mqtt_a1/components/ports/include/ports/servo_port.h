//
// Created by josemar on 04/01/2026.
//

#ifndef BROKER_MQTT_A1_SERVO_PORT_H
#define BROKER_MQTT_A1_SERVO_PORT_H

#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int gpio_num; // GPIO do sinal do servo
    uint32_t freq_hz; // 50Hz típico
    uint32_t duty_res_bits; // ex: 16
    uint32_t min_pulse_us; // ex: 500
    uint32_t max_pulse_us; // ex: 2400
} ServoPwmConfig;

typedef struct {
    bool (*init)(const ServoPwmConfig *cfg);

    bool (*set_pulse_us)(uint32_t pulse_us);
} ServoPort;

#endif //BROKER_MQTT_A1_SERVO_PORT_H

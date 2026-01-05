//
// Created by josemar on 04/01/2026.
//

#ifndef BROKER_MQTT_A1_SERVO_DOMAIN_H
#define BROKER_MQTT_A1_SERVO_DOMAIN_H

#pragma once
#include <stdint.h>

typedef struct {
    uint32_t min_pulse_us;
    uint32_t max_pulse_us;
} ServoPulseRange;

uint8_t servo_domain_clamp_angle(int angle_deg);

uint32_t servo_domain_angle_to_pulse_us(uint8_t angle_deg, ServoPulseRange range);

#endif //BROKER_MQTT_A1_SERVO_DOMAIN_H

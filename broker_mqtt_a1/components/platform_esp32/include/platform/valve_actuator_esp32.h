//
// Created by josemar on 05/01/2026.
//

#ifndef BROKER_MQTT_A1_VALVE_ACTUATOR_ESP32_H
#define BROKER_MQTT_A1_VALVE_ACTUATOR_ESP32_H

#pragma once
#include <stdbool.h>
#include <stdint.h>

bool platform_valve_actuator_init(void);

bool platform_valve_actuator_set_position_percent(uint8_t percent); // 0..100

#endif //BROKER_MQTT_A1_VALVE_ACTUATOR_ESP32_H

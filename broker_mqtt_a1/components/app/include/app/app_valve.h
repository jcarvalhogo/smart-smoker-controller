//
// Created by josemar on 05/01/2026.
//

#ifndef BROKER_MQTT_A1_APP_VALVE_H
#define BROKER_MQTT_A1_APP_VALVE_H

#pragma once
#include <stdint.h>

void app_valve_init(void);

// helpers de domínio
void app_valve_open(void);

void app_valve_close(void);

// posição 0..100%
void app_valve_set_position(uint8_t percent);

#endif //BROKER_MQTT_A1_APP_VALVE_H

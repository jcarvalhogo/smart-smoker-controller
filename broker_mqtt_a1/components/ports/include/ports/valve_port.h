//
// Created by josemar on 05/01/2026.
//

#ifndef BROKER_MQTT_A1_VALVE_PORT_H
#define BROKER_MQTT_A1_VALVE_PORT_H

#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool (*init)(void);

    bool (*set_position_percent)(uint8_t percent); // 0..100
} valve_port_t;

const valve_port_t *valve_port(void);

#endif //BROKER_MQTT_A1_VALVE_PORT_H

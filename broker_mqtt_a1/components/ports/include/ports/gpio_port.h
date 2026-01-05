//
// Created by josemar on 15/12/2025.
//

#ifndef BROKER_MQTT_A1_GPIO_PORT_H
#define BROKER_MQTT_A1_GPIO_PORT_H

#pragma once
#include <stdint.h>

typedef struct {
    bool (*set_direction_output)(uint32_t pin);
    bool (*set_level)(uint32_t pin, bool level);
} GpioPort;

GpioPort gpio_port(void);

#endif //BROKER_MQTT_A1_GPIO_PORT_H

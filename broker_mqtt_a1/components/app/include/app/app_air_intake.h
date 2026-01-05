//
// Created by josemar on 03/01/2026.
//

#ifndef BROKER_MQTT_A1_APP_AIR_INTAKE_H
#define BROKER_MQTT_A1_APP_AIR_INTAKE_H

#pragma once
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Initialize air intake actuator
 */
bool app_air_intake_init(void);

/**
 * @brief Set air intake opening position
 * @param position Opening position (0..180)
 */
bool app_air_intake_set_position(uint8_t position);

/**
 * @brief Fully open air intake
 */
static inline bool app_air_intake_open(void) {
    return app_air_intake_set_position(180);
}

/**
 * @brief Fully close air intake
 */
static inline bool app_air_intake_close(void) {
    return app_air_intake_set_position(0);
}

#endif // BROKER_MQTT_A1_APP_AIR_INTAKE_H

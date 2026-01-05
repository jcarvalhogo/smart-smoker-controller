//
// Created by josemar on 04/01/2026.
//

#ifndef BROKER_MQTT_A1_SERVO_ESP32_H
#define BROKER_MQTT_A1_SERVO_ESP32_H

#pragma once
#include "ports/servo_port.h"

// Retorna uma implementação de ServoPort baseada em LEDC (ESP-IDF)
ServoPort platform_servo_port(void);

#endif //BROKER_MQTT_A1_SERVO_ESP32_H

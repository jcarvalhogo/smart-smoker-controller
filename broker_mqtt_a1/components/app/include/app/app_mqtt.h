//
// Created by josemar on 15/12/2025.
//

#ifndef BROKER_MQTT_A1_APP_MQTT_H
#define BROKER_MQTT_A1_APP_MQTT_H
#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {


#endif

void app_mqtt_start(const char *broker_uri);

bool app_mqtt_is_ready(void);

/**
 * @brief Publica em MQTT. O tópico pode ser:
 *  - relativo: "telemetry/x" -> vira "JC_GO/telemetry/x"
 *  - absoluto: "JC_GO/telemetry/x" -> publica como está
 *  - com barra: "/telemetry/x" -> vira "JC_GO/telemetry/x"
 */
bool app_mqtt_publish(const char *topic, const char *payload, int qos, bool retain);

/**
 * @brief Publica com printf-style (monta payload internamente).
 */
bool app_mqtt_publishf(const char *topic, int qos, bool retain, const char *fmt, ...);

#ifdef __cplusplus
}
#endif
#endif //BROKER_MQTT_A1_APP_MQTT_H

//
// Created by josemar on 03/01/2026.
//

#ifndef BROKER_MQTT_A1_APP_DHT22_H
#define BROKER_MQTT_A1_APP_DHT22_H

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Inicializa a task de leitura do DHT22
     *
     * Cria uma task FreeRTOS que lê temperatura e umidade
     * periodicamente (>= 2s, conforme especificação do DHT22).
     */
    void app_dht22_start(void);

#ifdef __cplusplus
}
#endif


#endif //BROKER_MQTT_A1_APP_DHT22_H
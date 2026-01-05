//
// Created by josemar on 05/01/2026.
//

#include "app/app_valve.h"
#include "ports/valve_port.h"

#include "esp_log.h"

static const char *TAG = "app_valve";

static const valve_port_t *s_port = NULL;
static bool s_initialized = false; // <<< EXTRA OPCIONAL

void app_valve_init(void) {
    // Evita reinicialização acidental
    if (s_initialized) {
        ESP_LOGI(TAG, "Valve already initialized");
        return;
    }

    s_port = valve_port();

    if (!s_port || !s_port->init || !s_port->set_position_percent) {
        ESP_LOGE(TAG, "valve_port invalid");
        s_port = NULL;
        return;
    }

    if (!s_port->init()) {
        ESP_LOGE(TAG, "Valve actuator init failed");
        s_port = NULL;
        return;
    }

    // Estado inicial seguro: válvula fechada
    if (!s_port->set_position_percent(0)) {
        ESP_LOGE(TAG, "Valve default close failed");
    }

    s_initialized = true; // <<< MARCA COMO INICIALIZADO
    ESP_LOGI(TAG, "Valve initialized");
}

void app_valve_set_position(uint8_t percent) {
    if (percent > 100) percent = 100;

    if (!s_initialized) {
        app_valve_init();
        if (!s_initialized) return;
    }

    if (!s_port->set_position_percent(percent)) {
        ESP_LOGE(TAG, "Valve set position failed (%u)", percent);
    }
}

void app_valve_open(void) {
    app_valve_set_position(100);
}

void app_valve_close(void) {
    app_valve_set_position(0);
}

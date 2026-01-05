//
// Created by josemar on 05/01/2026.
//

#include "ports/valve_port.h"
#include "platform/valve_actuator_esp32.h"

const valve_port_t *valve_port(void) {
    static valve_port_t port = {
        .init = platform_valve_actuator_init,
        .set_position_percent = platform_valve_actuator_set_position_percent,
    };
    return &port;
}

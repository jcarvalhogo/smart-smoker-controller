//
// Created by josemar on 15/12/2025.
//
#include "ports/gpio_port.h"
#include "driver/gpio.h"

static bool gpio_set_dir_out(uint32_t pin) {
    gpio_config_t io = {
        .pin_bit_mask = 1ULL << pin,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    return gpio_config(&io) == ESP_OK;
}

static bool gpio_set_lvl(uint32_t pin, bool level) {
    return gpio_set_level((gpio_num_t) pin, level ? 1 : 0) == ESP_OK;
}

GpioPort gpio_port(void) {
    return (GpioPort){
        .set_direction_output = gpio_set_dir_out,
        .set_level = gpio_set_lvl,
    };
}

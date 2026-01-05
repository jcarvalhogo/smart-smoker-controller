//
// Created by josemar on 05/01/2026.
//

#include "platform/valve_actuator_esp32.h"

#include "driver/ledc.h"
#include "esp_err.h"
#include "driver/gpio.h"


// =====================
// Hardware config
// =====================
#define VALVE_SERVO_GPIO        GPIO_NUM_19   // <-- troque aqui se necessário

#define VALVE_LEDC_MODE         LEDC_LOW_SPEED_MODE
#define VALVE_LEDC_TIMER        LEDC_TIMER_1          // usa TIMER_1 para reduzir chance de conflito
#define VALVE_LEDC_CHANNEL      LEDC_CHANNEL_2        // usa CHANNEL_2 para reduzir chance de conflito

// =====================
// Servo/PWM config
// =====================
#define SERVO_FREQ_HZ           50
#define SERVO_PERIOD_US         20000

// Ajuste se seu servo precisar (muitos aceitam ~500-2500us)
#define SERVO_MIN_US            500
#define SERVO_MAX_US            2500

#define SERVO_DUTY_RES          LEDC_TIMER_16_BIT

static bool s_inited = false;

static uint32_t us_to_duty(uint32_t us) {
    const uint32_t duty_max = (1UL << SERVO_DUTY_RES) - 1;
    return (us * duty_max) / SERVO_PERIOD_US;
}

static uint32_t percent_to_pulse_us(uint8_t percent) {
    if (percent > 100) percent = 100;
    const uint32_t span = (SERVO_MAX_US - SERVO_MIN_US);
    return SERVO_MIN_US + ((uint32_t) percent * span) / 100U;
}

bool platform_valve_actuator_init(void) {
    if (s_inited) return true;

    ledc_timer_config_t tcfg = {
        .speed_mode = VALVE_LEDC_MODE,
        .timer_num = VALVE_LEDC_TIMER,
        .duty_resolution = SERVO_DUTY_RES,
        .freq_hz = SERVO_FREQ_HZ,
        .clk_cfg = LEDC_AUTO_CLK,
    };

    if (ledc_timer_config(&tcfg) != ESP_OK) return false;

    ledc_channel_config_t chcfg = {
        .gpio_num = VALVE_SERVO_GPIO,
        .speed_mode = VALVE_LEDC_MODE,
        .channel = VALVE_LEDC_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = VALVE_LEDC_TIMER,
        .duty = 0,
        .hpoint = 0,
    };

    if (ledc_channel_config(&chcfg) != ESP_OK) return false;

    s_inited = true;

    // posição inicial: fechado
    return platform_valve_actuator_set_position_percent(0);
}

bool platform_valve_actuator_set_position_percent(uint8_t percent) {
    if (!s_inited) {
        if (!platform_valve_actuator_init()) return false;
    }

    const uint32_t pulse_us = percent_to_pulse_us(percent);
    const uint32_t duty = us_to_duty(pulse_us);

    if (ledc_set_duty(VALVE_LEDC_MODE, VALVE_LEDC_CHANNEL, duty) != ESP_OK) return false;
    return ledc_update_duty(VALVE_LEDC_MODE, VALVE_LEDC_CHANNEL) == ESP_OK;
}

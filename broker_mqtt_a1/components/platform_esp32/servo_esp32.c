//
// Created by josemar on 04/01/2026.
//

#include "platform/servo_esp32.h"

#include "driver/ledc.h"
#include "esp_err.h"

static ServoPwmConfig s_cfg;
static bool s_inited = false;

// Fixos (um servo). Se quiser múltiplos servos, a gente evolui para ctx por instância.
static const ledc_mode_t     LEDC_MODE   = LEDC_LOW_SPEED_MODE;
static const ledc_timer_t    LEDC_TIMER  = LEDC_TIMER_0;
static const ledc_channel_t  LEDC_CH     = LEDC_CHANNEL_0;

static uint32_t clamp_u32(uint32_t v, uint32_t lo, uint32_t hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static uint32_t pulse_us_to_duty(uint32_t pulse_us) {
    // duty = pulse_us / period_us * (2^res - 1)
    uint32_t period_us = 1000000UL / s_cfg.freq_hz;
    pulse_us = clamp_u32(pulse_us, 0, period_us);

    uint32_t max_duty = (1UL << s_cfg.duty_res_bits) - 1;
    uint64_t duty = (uint64_t)pulse_us * max_duty + (period_us / 2);
    duty /= period_us;
    return (uint32_t)duty;
}

static bool servo_init_impl(const ServoPwmConfig *cfg) {
    if (!cfg) return false;
    s_cfg = *cfg;

    ledc_timer_config_t t = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = s_cfg.freq_hz,
        .duty_resolution  = (ledc_timer_bit_t)s_cfg.duty_res_bits,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    if (ledc_timer_config(&t) != ESP_OK) return false;

    ledc_channel_config_t ch = {
        .gpio_num   = s_cfg.gpio_num,
        .speed_mode = LEDC_MODE,
        .channel    = LEDC_CH,
        .intr_type  = LEDC_INTR_DISABLE,
        .timer_sel  = LEDC_TIMER,
        .duty       = 0,
        .hpoint     = 0
    };
    if (ledc_channel_config(&ch) != ESP_OK) return false;

    s_inited = true;
    return true;
}

static bool servo_set_pulse_impl(uint32_t pulse_us) {
    if (!s_inited) return false;

    pulse_us = clamp_u32(pulse_us, s_cfg.min_pulse_us, s_cfg.max_pulse_us);
    uint32_t duty = pulse_us_to_duty(pulse_us);

    if (ledc_set_duty(LEDC_MODE, LEDC_CH, duty) != ESP_OK) return false;
    return ledc_update_duty(LEDC_MODE, LEDC_CH) == ESP_OK;
}

ServoPort platform_servo_port(void) {
    return (ServoPort){
        .init = servo_init_impl,
        .set_pulse_us = servo_set_pulse_impl,
    };
}

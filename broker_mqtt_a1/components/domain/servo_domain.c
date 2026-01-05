//
// Created by josemar on 04/01/2026.
//

#include "domain/servo_domain.h"

static uint32_t clamp_u32(uint32_t v, uint32_t lo, uint32_t hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

uint8_t servo_domain_clamp_angle(int angle_deg) {
    if (angle_deg < 0) return 0;
    if (angle_deg > 180) return 180;
    return (uint8_t) angle_deg;
}

uint32_t servo_domain_angle_to_pulse_us(uint8_t angle_deg, ServoPulseRange range) {
    if (angle_deg > 180) angle_deg = 180;

    uint32_t span = (range.max_pulse_us > range.min_pulse_us)
                        ? (range.max_pulse_us - range.min_pulse_us)
                        : 0;

    uint32_t pulse = range.min_pulse_us + (uint32_t)((uint64_t) span * angle_deg / 180ULL);
    return clamp_u32(pulse, range.min_pulse_us, range.max_pulse_us);
}

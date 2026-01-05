#include "app/app_wifi_led.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ports/gpio_port.h"
#include "ports/wifi_port.h"

typedef enum {
    LED_ST_CONNECTING = 0,
    LED_ST_CONNECTED,
    LED_ST_DISCONNECTED,
    LED_ST_FAILED,
} LedState;

static volatile LedState g_led_state = LED_ST_CONNECTING;

typedef struct {
    uint32_t led_gpio;
    GpioPort gpio;
} LedCtx;

static void wifi_status_cb(WifiStatus st, void *user) {
    (void) user;
    switch (st) {
        case WIFI_STATUS_CONNECTING: g_led_state = LED_ST_CONNECTING;
            break;
        case WIFI_STATUS_CONNECTED: g_led_state = LED_ST_CONNECTED;
            break;
        case WIFI_STATUS_DISCONNECTED: g_led_state = LED_ST_DISCONNECTED;
            break;
        case WIFI_STATUS_FAILED: g_led_state = LED_ST_FAILED;
            break;
        default: break;
    }
}

static void led_task(void *arg) {
    LedCtx *ctx = (LedCtx *) arg;

    ctx->gpio.set_direction_output(ctx->led_gpio);

    for (;;) {
        LedState st = g_led_state;

        if (st == LED_ST_CONNECTED) {
            ctx->gpio.set_level(ctx->led_gpio, true);
            vTaskDelay(pdMS_TO_TICKS(500));
            continue;
        }

        if (st == LED_ST_CONNECTING) {
            ctx->gpio.set_level(ctx->led_gpio, true);
            vTaskDelay(pdMS_TO_TICKS(200));
            ctx->gpio.set_level(ctx->led_gpio, false);
            vTaskDelay(pdMS_TO_TICKS(200));
            continue;
        }

        if (st == LED_ST_DISCONNECTED) {
            ctx->gpio.set_level(ctx->led_gpio, true);
            vTaskDelay(pdMS_TO_TICKS(150));
            ctx->gpio.set_level(ctx->led_gpio, false);
            vTaskDelay(pdMS_TO_TICKS(850));
            continue;
        }

        // FAILED: 2 piscadas rápidas + pausa
        ctx->gpio.set_level(ctx->led_gpio, true);
        vTaskDelay(pdMS_TO_TICKS(100));
        ctx->gpio.set_level(ctx->led_gpio, false);
        vTaskDelay(pdMS_TO_TICKS(100));
        ctx->gpio.set_level(ctx->led_gpio, true);
        vTaskDelay(pdMS_TO_TICKS(100));
        ctx->gpio.set_level(ctx->led_gpio, false);
        vTaskDelay(pdMS_TO_TICKS(700));
    }
}

void app_wifi_led_start(const char *ssid, const char *pass, uint32_t led_gpio) {
    static LedCtx ctx; // estático para não morrer ao sair da função
    ctx.led_gpio = led_gpio;
    ctx.gpio = gpio_port();

    g_led_state = LED_ST_CONNECTING;

    xTaskCreate(led_task, "led_task", 2048, &ctx, 5, NULL);

    WifiPort wifi = wifi_port();
    wifi.start_sta(ssid, pass, wifi_status_cb, NULL);
}

//
// Created by josemar on 15/12/2025.
//

#include "app/app_mqtt.h"
#include "app/app_air_intake.h"
#include "app/app_valve.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "esp_log.h"
#include "mqtt_client.h"

#define MQTT_BASE_TOPIC "JC_GO"

#define AIR_INTAKE_CMD_TOPIC   "air/intake"   // relative -> JC_GO/air/intake
#define GAS_VALVE_CMD_TOPIC    "gas/valve"    // relative -> JC_GO/gas/valve

static const char *TAG = "app_mqtt";

static esp_mqtt_client_handle_t s_client = NULL;
static volatile bool s_mqtt_connected = false;
static volatile bool s_mqtt_started = false;

/* subscribed full topics */
static char s_air_intake_full_topic[256];
static char s_gas_valve_full_topic[256];

static void build_topic(char *out, size_t out_sz, const char *topic) {
    if (!out || out_sz == 0) return;
    out[0] = '\0';

    if (!topic || topic[0] == '\0') return;

    // remove leading '/' if absolute like "/servo"
    if (topic[0] == '/') topic++;

    // if already starts with base, do not duplicate
    size_t base_len = strlen(MQTT_BASE_TOPIC);
    if (strncmp(topic, MQTT_BASE_TOPIC, base_len) == 0 &&
        (topic[base_len] == '\0' || topic[base_len] == '/')) {
        snprintf(out, out_sz, "%s", topic);
        return;
    }

    snprintf(out, out_sz, MQTT_BASE_TOPIC "/%s", topic);
}

bool app_mqtt_is_ready(void) {
    return (s_mqtt_connected && s_client != NULL);
}

bool app_mqtt_publish(const char *topic, const char *payload, int qos, bool retain) {
    if (!app_mqtt_is_ready() || !topic || !payload) return false;

    char full_topic[256];
    build_topic(full_topic, sizeof(full_topic), topic);

    int msg_id = esp_mqtt_client_publish(
        s_client,
        full_topic,
        payload,
        0, // auto len
        qos,
        retain ? 1 : 0
    );

    return msg_id >= 0;
}

bool app_mqtt_publishf(const char *topic, int qos, bool retain, const char *fmt, ...) {
    if (!fmt) return false;

    char payload[128];

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(payload, sizeof(payload), fmt, ap);
    va_end(ap);

    return app_mqtt_publish(topic, payload, qos, retain);
}

/* simple parser for {"angle":90} (accepts spaces/quotes/signs) */
static bool parse_angle_from_json(const char *json, int *out_angle) {
    if (!json || !out_angle) return false;

    const char *p = strstr(json, "\"angle\"");
    if (!p) return false;

    p = strchr(p, ':');
    if (!p) return false;
    p++;

    while (*p && isspace((unsigned char)*p)) p++;

    char *end = NULL;
    long v = strtol(p, &end, 10);
    if (end == p) return false;

    *out_angle = (int) v;
    return true;
}

/* simple parser for {"percent":35} */
static bool parse_percent_from_json(const char *json, int *out_percent) {
    if (!json || !out_percent) return false;

    const char *p = strstr(json, "\"percent\"");
    if (!p) return false;

    p = strchr(p, ':');
    if (!p) return false;
    p++;

    while (*p && isspace((unsigned char)*p)) p++;

    char *end = NULL;
    long v = strtol(p, &end, 10);
    if (end == p) return false;

    *out_percent = (int) v;
    return true;
}

/* simple parser for {"action":"open"} */
static bool parse_action_from_json(const char *json, char *out, size_t out_sz) {
    if (!json || !out || out_sz == 0) return false;

    const char *p = strstr(json, "\"action\"");
    if (!p) return false;

    p = strchr(p, ':');
    if (!p) return false;
    p++;

    while (*p && isspace((unsigned char)*p)) p++;
    if (*p == '\"') p++;

    size_t i = 0;
    while (*p && *p != '\"' && *p != ',' && *p != '}' && !isspace((unsigned char)*p)) {
        if (i + 1 < out_sz) out[i++] = (char) tolower((unsigned char) *p);
        p++;
    }
    out[i] = '\0';

    return i > 0;
}

static void mqtt_event_handler(
    void *handler_args,
    esp_event_base_t base,
    int32_t event_id,
    void *event_data
) {
    (void) handler_args;
    (void) base;
    (void) event_id;

    esp_mqtt_event_handle_t e = (esp_mqtt_event_handle_t) event_data;

    switch (e->event_id) {
        case MQTT_EVENT_CONNECTED:
            s_mqtt_connected = true;
            ESP_LOGI(TAG, "MQTT connected");

            build_topic(s_air_intake_full_topic, sizeof(s_air_intake_full_topic), AIR_INTAKE_CMD_TOPIC);
            esp_mqtt_client_subscribe(s_client, s_air_intake_full_topic, 1);
            ESP_LOGI(TAG, "Subscribed: %s", s_air_intake_full_topic);

            build_topic(s_gas_valve_full_topic, sizeof(s_gas_valve_full_topic), GAS_VALVE_CMD_TOPIC);
            esp_mqtt_client_subscribe(s_client, s_gas_valve_full_topic, 1);
            ESP_LOGI(TAG, "Subscribed: %s", s_gas_valve_full_topic);

            break;

        case MQTT_EVENT_DISCONNECTED:
            s_mqtt_connected = false;
            ESP_LOGW(TAG, "MQTT disconnected");
            break;

        case MQTT_EVENT_DATA: {
            char topic[256];
            int tlen = (e->topic_len < (int) sizeof(topic) - 1) ? e->topic_len : (int) sizeof(topic) - 1;
            memcpy(topic, e->topic, tlen);
            topic[tlen] = '\0';

            char payload[256];
            int dlen = (e->data_len < (int) sizeof(payload) - 1) ? e->data_len : (int) sizeof(payload) - 1;
            memcpy(payload, e->data, dlen);
            payload[dlen] = '\0';

            /* AIR INTAKE */
            if (strcmp(topic, s_air_intake_full_topic) == 0) {
                int angle = 0;
                if (parse_angle_from_json(payload, &angle)) {
                    ESP_LOGI(TAG, "Air intake cmd: angle=%d", angle);
                    if (!app_air_intake_set_position((uint8_t) angle)) {
                        ESP_LOGW(TAG, "Failed to enqueue air intake angle=%d", angle);
                    }
                } else {
                    ESP_LOGW(TAG, "Invalid air intake JSON: %s", payload);
                }
            }

            /* GAS VALVE */
            if (strcmp(topic, s_gas_valve_full_topic) == 0) {
                int percent = -1;
                char action[16] = {0};

                if (parse_percent_from_json(payload, &percent)) {
                    if (percent < 0) percent = 0;
                    if (percent > 100) percent = 100;

                    app_valve_set_position((uint8_t) percent);
                    ESP_LOGI(TAG, "Gas valve cmd: percent=%d", percent);
                } else if (parse_action_from_json(payload, action, sizeof(action))) {
                    if (strcmp(action, "open") == 0) {
                        app_valve_open();
                        ESP_LOGI(TAG, "Gas valve cmd: open");
                    } else if (strcmp(action, "close") == 0) {
                        app_valve_close();
                        ESP_LOGI(TAG, "Gas valve cmd: close");
                    } else {
                        ESP_LOGW(TAG, "Invalid gas valve action: %s payload=%s", action, payload);
                    }
                } else {
                    ESP_LOGW(TAG, "Invalid gas valve JSON: %s", payload);
                }
            }

            break;
        }

        default:
            break;
    }
}

void app_mqtt_start(const char *broker_uri) {
    if (s_mqtt_started) {
        ESP_LOGW(TAG, "MQTT already started");
        return;
    }
    s_mqtt_started = true;

    ESP_LOGI(TAG, "Starting MQTT: %s", broker_uri);

    esp_mqtt_client_config_t cfg = {
        .broker.address.uri = broker_uri,
        .credentials.client_id = "broker_mqtt_a1",
    };

    s_client = esp_mqtt_client_init(&cfg);

    esp_mqtt_client_register_event(
        s_client,
        ESP_EVENT_ANY_ID,
        mqtt_event_handler,
        NULL
    );

    esp_mqtt_client_start(s_client);
}

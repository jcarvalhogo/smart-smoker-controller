#pragma once
#include <stdbool.h>
#include "ports/wifi_port.h"

bool platform_wifi_start_sta(const char *ssid, const char *pass,
                             wifi_status_cb_t cb, void *user);

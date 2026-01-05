idf_component_register(
        SRCS
        "gpio_esp32.c"
        "wifi_esp32.c"
        "servo_esp32.c"
        "valve_actuator_esp32.c"
        INCLUDE_DIRS "include"
        REQUIRES ports nvs_flash esp_wifi esp_event esp_netif esp_driver_gpio
        PRIV_REQUIRES esp_driver_ledc esp_driver_i2c
)
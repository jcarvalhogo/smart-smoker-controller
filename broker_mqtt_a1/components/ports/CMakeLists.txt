idf_component_register(
        SRCS
        "wifi_port_esp32.c"
        "valve_port_esp32.c"
        INCLUDE_DIRS "include"
        REQUIRES platform_esp32
)

cmake_minimum_required(VERSION 3.22)

set(EXTRA_COMPONENT_DIRS
        "${CMAKE_CURRENT_LIST_DIR}/components"
        "${CMAKE_CURRENT_LIST_DIR}/external_components"
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(broker_mqtt_a1)

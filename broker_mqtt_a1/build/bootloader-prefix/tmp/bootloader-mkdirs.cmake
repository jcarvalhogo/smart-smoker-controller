# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf/components/bootloader/subproject"
  "/l/disk0/josemar/development/pessoal/curso-iot/esp32/projects/broker_mqtt_a1/build/bootloader"
  "/l/disk0/josemar/development/pessoal/curso-iot/esp32/projects/broker_mqtt_a1/build/bootloader-prefix"
  "/l/disk0/josemar/development/pessoal/curso-iot/esp32/projects/broker_mqtt_a1/build/bootloader-prefix/tmp"
  "/l/disk0/josemar/development/pessoal/curso-iot/esp32/projects/broker_mqtt_a1/build/bootloader-prefix/src/bootloader-stamp"
  "/l/disk0/josemar/development/pessoal/curso-iot/esp32/projects/broker_mqtt_a1/build/bootloader-prefix/src"
  "/l/disk0/josemar/development/pessoal/curso-iot/esp32/projects/broker_mqtt_a1/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/l/disk0/josemar/development/pessoal/curso-iot/esp32/projects/broker_mqtt_a1/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/l/disk0/josemar/development/pessoal/curso-iot/esp32/projects/broker_mqtt_a1/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()

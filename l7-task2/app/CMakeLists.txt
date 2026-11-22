cmake_minimum_required(VERSION 3.20.0)

list(APPEND DTS_ROOT ${CMAKE_CURRENT_LIST_DIR}/..)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(l7_task2_sensor_set_shell)

target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../drivers/led_sensor
)

target_sources(app PRIVATE
    src/main.c
    src/sensor_shell.c
    ${CMAKE_CURRENT_LIST_DIR}/../drivers/led_sensor/led_sensor.c
)

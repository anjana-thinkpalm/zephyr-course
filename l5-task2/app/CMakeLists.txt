
cmake_minimum_required(VERSION 3.20.0)

# Register the custom board directory.
list(APPEND BOARD_ROOT ${CMAKE_CURRENT_LIST_DIR}/..)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(l5_task2_hello_world)

target_sources(app PRIVATE src/main.c)

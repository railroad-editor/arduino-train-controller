cmake_minimum_required(VERSION 3.8)

set(CMAKE_TOOLCHAIN_FILE /Users/tozawa/Projects/Arduino-CMake-NG/cmake/Arduino-Toolchain.cmake)
include_directories(.)
include_directories(libs/ArduinoJson-5.13.2/src)
include_directories(libs/ArduinoSTL-1.1.0/src)

project(arduino_train_controller LANGUAGES C CXX ASM)
get_board_id(board_id mega atmega2560)

file(GLOB TRAIN_CONTROLER_SRCS
        "*.h"
        "*.cpp"
        "*.ino"
        )

add_arduino_executable(arduino_train_controller ${board_id} ${TRAIN_CONTROLER_SRCS})
upload_arduino_target(arduino_train_controller ${board_id} arduino-train-controller.ino)



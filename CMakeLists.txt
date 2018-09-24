cmake_minimum_required(VERSION 3.8)

set(CMAKE_TOOLCHAIN_FILE /Users/tozawa/Projects/Arduino-CMake-NG/cmake/Arduino-Toolchain.cmake)
include_directories(.)
include_directories(libs/ArduinoJson-5.13.2/src)
include_directories(libs/ArduinoSTL-1.1.0/src)

project(arduino_train_controller LANGUAGES C CXX ASM)
get_board_id(board_id nano atmega328)

file(GLOB TRAIN_CONTROLER_SRCS
        "*.h"
        "*.cpp"
        "*.ino"
        )

add_arduino_executable(TrainController ${board_id} ${TRAIN_CONTROLER_SRCS})
upload_arduino_target(TrainController ${board_id} TrainController.cpp)


#set(CMAKE_CXX_STANDARD 14)


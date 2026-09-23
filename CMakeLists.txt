cmake_minimum_required(VERSION 4.0)
project(parking_sensor)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
)

FetchContent_MakeAvailable(raylib)

add_executable(parking_sensor src/main.cpp
        src/Sensor.cpp
        src/Sensor.h
        src/ConsoleInput.cpp
        src/ConsoleInput.h
        src/Visualizer.cpp
        src/Visualizer.h
)

target_link_libraries(parking_sensor PRIVATE raylib)

cmake_minimum_required(VERSION 4.0)

project(parking_sensor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
)

FetchContent_MakeAvailable(raylib)

add_executable(
        parking_sensor

        src/main.cpp
        src/Sensor.cpp
        src/Sensor.h
        src/ConsoleInput.cpp
        src/ConsoleInput.h
        src/Visualizer.cpp
        src/Visualizer.h
        src/SharedDistance.h
        src/ProjectConfig.h
)

target_include_directories(
        parking_sensor
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(
        parking_sensor
        PRIVATE raylib
)

add_executable(
        sensor_tests

        tests/SensorTests.cpp
        src/Sensor.cpp
        src/Sensor.h
        src/ProjectConfig.h
)

target_include_directories(
        sensor_tests
        PRIVATE src
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(
        console_input_tests
        tests/ConsoleInputTests.cpp
        src/ConsoleInput.cpp
        src/Sensor.cpp
        src/Sensor.h
        src/ConsoleInput.h
        src/ProjectConfig.h
)

target_include_directories(
        console_input_tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(
        shared_distance_tests
        tests/SharedDistanceTests.cpp
)

target_include_directories(
        shared_distance_tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

enable_testing()

add_test(
        NAME SensorTests
        COMMAND $<TARGET_FILE:sensor_tests>
)

add_test(
        NAME ConsoleInputTests
        COMMAND $<TARGET_FILE:console_input_tests>
)

add_test(
        NAME SharedDistanceTests
        COMMAND $<TARGET_FILE:shared_distance_tests>
)
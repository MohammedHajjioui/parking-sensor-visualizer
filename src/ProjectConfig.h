
#ifndef PARKING_SENSOR_PROJECTCONFIG_H
#define PARKING_SENSOR_PROJECTCONFIG_H
#include <cstddef>

constexpr std::size_t SENSOR_COUNT = 4;

constexpr int SAFE_DISTANCE = 150;
constexpr int OBSTACLE_DISTANCE = 81;
constexpr int WARNING_DISTANCE = 41;
constexpr int BRAKE_DISTANCE = 16;

enum class AlertLevel {
    Safe,
    ObstacleDetected,
    Warning,
    Brake,
    Stop,
    NotDetected
};




#endif //PARKING_SENSOR_PROJECTCONFIG_H
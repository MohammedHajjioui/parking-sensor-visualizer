#ifndef PARKING_SENSOR_SENSOR_H
#define PARKING_SENSOR_SENSOR_H

#include <string>
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

class Sensor {
    public:
        Sensor(const std::string& name);

        bool setDistance(int distance);

        [[nodiscard]] const std::string& getName() const;
        [[nodiscard]] int getDistance() const;
        [[nodiscard]] AlertLevel getAlertLevel() const;

    private:
        std::string name_;
        int distance_{-1};
        AlertLevel level_{AlertLevel::NotDetected};
};

#endif // PARKING_SENSOR_SENSOR_H
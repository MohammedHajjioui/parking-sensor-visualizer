#ifndef PARKING_SENSOR_SENSOR_H
#define PARKING_SENSOR_SENSOR_H

#include <string>

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

        const std::string& getName() const;
        int getDistance() const;
        AlertLevel getAlertLevel() const;

    private:
        std::string name_;
        int distance_{-1};
        AlertLevel level_{AlertLevel::NotDetected};
};

#endif // PARKING_SENSOR_SENSOR_H
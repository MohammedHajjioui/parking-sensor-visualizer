#ifndef PARKING_SENSOR_SENSOR_H
#define PARKING_SENSOR_SENSOR_H

#include <string>
#include "ProjectConfig.h"

class Sensor {
    public:
        explicit Sensor(const std::string& name);

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
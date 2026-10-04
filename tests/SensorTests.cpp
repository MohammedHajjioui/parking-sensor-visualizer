#include "Sensor.h"

#include <cassert>

int main() {
    Sensor sensor{"Front Left"};

    assert(sensor.getAlertLevel() == AlertLevel::NotDetected);

    assert(sensor.setDistance(0));
    assert(sensor.getAlertLevel() == AlertLevel::Stop);

    assert(sensor.setDistance(15));
    assert(sensor.getAlertLevel() == AlertLevel::Stop);

    assert(sensor.setDistance(16));
    assert(sensor.getAlertLevel() == AlertLevel::Brake);

    assert(sensor.setDistance(40));
    assert(sensor.getAlertLevel() == AlertLevel::Brake);

    assert(sensor.setDistance(41));
    assert(sensor.getAlertLevel() == AlertLevel::Warning);

    assert(sensor.setDistance(80));
    assert(sensor.getAlertLevel() == AlertLevel::Warning);

    assert(sensor.setDistance(81));
    assert(sensor.getAlertLevel() == AlertLevel::ObstacleDetected);

    assert(sensor.setDistance(150));
    assert(sensor.getAlertLevel() == AlertLevel::ObstacleDetected);

    assert(sensor.setDistance(151));
    assert(sensor.getAlertLevel() == AlertLevel::Safe);

    assert(!sensor.setDistance(-1));
    assert(sensor.getDistance() == 151);
    assert(sensor.getAlertLevel() == AlertLevel::Safe);
}
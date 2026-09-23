#include "Sensor.h"

Sensor::Sensor(const std::string &name)
    : name_(name){
    level_ = AlertLevel::NotDetected;
    distance_ = -1;
}

bool Sensor::setDistance(int distance){
    if (distance < 0) return false;
    if (distance > SAFE_DISTANCE) level_ = AlertLevel::Safe;
    else if (distance >= OBSTACLE_DISTANCE) level_ = AlertLevel::ObstacleDetected;
    else if (distance >= WARNING_DISTANCE) level_ = AlertLevel::Warning;
    else if (distance >= BRAKE_DISTANCE) level_ = AlertLevel::Brake;
    else level_ = AlertLevel::Stop;
    distance_ = distance;
    return true;
}

const std::string & Sensor::getName() const {
    return name_;
}

int Sensor::getDistance() const {
    return distance_;
}

AlertLevel Sensor::getAlertLevel() const {
    return level_;
}


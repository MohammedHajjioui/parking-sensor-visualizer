#include <iostream>
#include "Sensor.h"
#include <string>
#include <array>

constexpr std::size_t SENSOR_COUNT = 4;

using AllSensors = std::array<Sensor, SENSOR_COUNT>;

bool isValid (std::array<Sensor, SENSOR_COUNT>& sensors);
bool printSensorAlert(const Sensor &sensorI);
void printMessage (const std::array<Sensor, SENSOR_COUNT>& sensors);
//int minDistanceAndSensor (const std::array<MySensor, SENSOR_COUNT>& sensors);
//AlertLevel getAlertLevel(int distance);

int main() {
    AllSensors sensors{
        Sensor {"Front Left"},
        Sensor {"Front Right"},
        Sensor {"Rear Left"},
        Sensor {"Rear Right"}
    };

    while (true) {
        if (!isValid(sensors)) {
            std::cout << "Program terminated\n";
            return 0;
        }
        printMessage(sensors);

    }
}

bool isValid (std::array<Sensor, SENSOR_COUNT>& sensors) {
    int value;
    std::cout << "\n";
    for (int i = 0; i < sensors.size(); i++) {
        std::cout << "Enter "<< (sensors)[i].getName() << " distance (-1 to exit): ";
        if (!(std::cin >> value)) {
            std::cout << "Input non valido\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            i--;
            continue;
        }
        if (value ==-1) {
            return false;
        }
        if (!sensors[i].setDistance(value)) {
            std::cout << "Distance can't be negative\n";
            i--;
        }
    }

    return true;
}

bool printSensorAlert(const Sensor &sensorI) {
    bool isActive = true;
    std::cout  << sensorI.getName() << " sensor --> ";

    switch (sensorI.getAlertLevel()) {
        case AlertLevel::Safe:
            std::cout  << "No nearby obstacle\n";
            isActive = false;
            break;

        case AlertLevel::ObstacleDetected:
            std::cout << "Obstacle detected\n";
            break;

        case AlertLevel::Warning:
            std::cout <<  "Warning!\n";
            break;

        case AlertLevel::Brake:
            std::cout << "Brake!\n";
            break;

        case AlertLevel::Stop:
            std::cout << "STOP!!\n" ;
            break;

        case AlertLevel::NotDetected:
            std::cout << "ERROR: sensore non in funzione.\n" ;// per ora non dovrebbe accadere dopo un input valido
            isActive = false;
            break;
    }

    std::cout  << "distance: " << sensorI.getDistance() << std::endl;
    return isActive;
}

void printMessage (const std::array<Sensor, SENSOR_COUNT> &sensors) {
    int nActive = 0;

    for (const auto & sensor : sensors) {
        std::cout << "\n";
        nActive = nActive + printSensorAlert(sensor);
    }
    std::cout << "\nActive sensors in this cycle: " << nActive;
}

/*int minDistanceAndSensor (const std::array<MySensor, SENSOR_COUNT>& sensors) {
    int out=0;
    int dist= (sensors)[0].dist;
    for (int i = 1; i < sensors.size(); i++) {
        if ((sensors)[i].dist < dist) {
            out = i;
            dist = (sensors)[i].dist;
        }
    }
    return out;
}

AlertLevel getAlertLevel(int distance) {
    if (distance > SAFE_DISTANCE) {
        return AlertLevel::Safe;
    }
    if (distance >= OBSTACLE_DISTANCE) {
        return AlertLevel::ObstacleDetected;
    }
    if (distance >= WARNING_DISTANCE) {
        return AlertLevel::Warning;
    }
    if (distance >= BRAKE_DISTANCE) {
        return AlertLevel::Brake;
    }
    return AlertLevel::Stop;
}*/

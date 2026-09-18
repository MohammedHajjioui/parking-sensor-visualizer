#include <iostream>
#include <string>
#include <array>

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

struct MySensor {
    std::string name;
    int dist;
    AlertLevel level;
};

using Sensors = std::array<MySensor, SENSOR_COUNT>;

bool isValid (std::array<MySensor, SENSOR_COUNT>& sensors);
//int minDistanceAndSensor (const std::array<MySensor, SENSOR_COUNT>& sensors);
AlertLevel getAlertLevel(int distance);
bool printSensorAlert(const MySensor &sensorI);
void printMessage (const std::array<MySensor, SENSOR_COUNT>& sensors);

int main() {
    Sensors sensors{{
        {"Front Left",  -1, AlertLevel::NotDetected},
        {"Front Right", -1, AlertLevel::NotDetected},
        {"Rear Left",   -1, AlertLevel::NotDetected},
        {"Rear Right",  -1, AlertLevel::NotDetected}
    }};


    while (true) {
        if (!isValid(sensors)) {
            std::cout << "Program terminated\n";
            return 0;
        }
        //int ref = minDistanceAndSensor(sensors);
        printMessage(sensors);

    }
}

bool isValid (std::array<MySensor, SENSOR_COUNT>& sensors) {
    std::cout << "\n";
    for (int i = 0; i < sensors.size(); i++) {
        std::cout << "Enter "<< (sensors)[i].name << " distance (-1 to exit): ";
        if (!(std::cin >> (sensors)[i].dist)) {
            std::cout << "Input non valido\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            i--;
            continue;
        }
        if ((sensors)[i].dist <-1) {
            std::cout << "Distance can't be negative\n";
            i--;
            continue;
        }
        if ((sensors)[i].dist ==-1) {
            return false;
        }
        sensors[i].level = getAlertLevel(sensors[i].dist);
    }

    return true;
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
}*/

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
}

bool printSensorAlert(const MySensor &sensorI) {
    bool isActive = true;
    std::cout  << sensorI.name << " sensor --> ";

    switch (sensorI.level) {
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

    std::cout  << "distance: " << sensorI.dist << std::endl;
    return isActive;
}

void printMessage (const std::array<MySensor, SENSOR_COUNT> &sensors) {
    int nActive = 0;

    for (const auto & sensor : sensors) {
        std::cout << "\n";
        nActive = nActive + printSensorAlert(sensor);
    }
    std::cout << "\nActive sensors in this cycle: " << nActive;
}

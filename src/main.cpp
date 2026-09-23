#include <iostream>
#include "Sensor.h"
#include "ConsoleInput.h"
#include "visualizer.h"
#include "ProjectConfig.h"
#include <string>
#include <array>

using AllSensors = std::array<Sensor, SENSOR_COUNT>;

int main() {
    runVisualizer();
    return 0;

    AllSensors sensors{
        Sensor {"Front Left"},
        Sensor {"Front Right"},
        Sensor {"Rear Left"},
        Sensor {"Rear Right"}
    };

    while (true) {
        if (!isValid(sensors)) {
            return 0;
        }
        printMessage(sensors);

    }
}

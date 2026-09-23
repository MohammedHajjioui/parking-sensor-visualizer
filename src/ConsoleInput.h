//
// Created by Momo on 23/09/2026.
//

#ifndef PARKING_SENSOR_CONSOLEINPUT_H
#define PARKING_SENSOR_CONSOLEINPUT_H
#include <array>
#include "ProjectConfig.h"
#include "Sensor.h"


bool isValid (std::array<Sensor, SENSOR_COUNT>& sensors);
bool printSensorAlert(const Sensor &sensorI);
void printMessage (const std::array<Sensor, SENSOR_COUNT>& sensors);

class ConsoleInput {
};


#endif //PARKING_SENSOR_CONSOLEINPUT_H
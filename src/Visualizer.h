//
// Created by Momo on 23/09/2026.
//

#ifndef PARKING_SENSOR_VISUALIZER_H
#define PARKING_SENSOR_VISUALIZER_H

#include "Sensor.h"
#include "SharedDistance.h"

void runVisualizer(
    std::array<Sensor, SENSOR_COUNT>& sensors,
    std::array<SharedDistance, SENSOR_COUNT>& sharedDistance
);

#endif // PARKING_SENSOR_VISUALIZER_H
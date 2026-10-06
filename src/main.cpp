#include "Sensor.h"
#include "ConsoleInput.h"
#include "visualizer.h"
#include "ProjectConfig.h"
#include "SharedDistance.h"
#include <string>
#include <array>

#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>

using AllSharedDistance = std::array<SharedDistance, SENSOR_COUNT>;

bool isValid2(AllSharedDistance & sharedDistances, const AllSensors & sensors);

int main() {

    AllSensors sensors{
        Sensor {"Front Left"},
        Sensor {"Front Right"},
        Sensor {"Rear Left"},
        Sensor {"Rear Right"}
    };

    AllSharedDistance sharedDistances{};
    std::atomic<bool> running{true};

    std::thread acquisitionThread([&sharedDistances, &running, &sensors]() {
        std::size_t index = 0;

        while (running.load()) {
            int value;

            std::cout << "Enter "
                      << sensors[index].getName()
                      << " distance: ";

            if (!readDistance(std::cin, value)) {
                if (std::cin.eof()) {
                    break; //non continuiamo ad aspettare all'infinito
                }

                continue;
            }

            // Se la finestra è stata chiusa mentre aspettavamo l'input,
            // non pubblichiamo un'altra misura.
            if (!running.load()) {
                break;
            }

            SharedDistance& current = sharedDistances[index];

            {
                std::lock_guard<std::mutex> lock(current.mutex);

                if (value != current.value) {
                    current.value = value;
                    current.hasNewValue = true;
                }
            }

            index = (index + 1) % SENSOR_COUNT;
        }
    });

    runVisualizer(sensors, sharedDistances);

    running.store(false);
    acquisitionThread.join();

    return 0;
}

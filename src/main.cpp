#include "Sensor.h"
#include "visualizer.h"
#include "ProjectConfig.h"
#include "SharedDistance.h"
#include <string>
#include <array>

#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>

using AllSensors = std::array<Sensor, SENSOR_COUNT>;
using AllSharedDistance = std::array<SharedDistance, SENSOR_COUNT>;

bool isValid2(AllSharedDistance & sharedDistances, const AllSensors & sensors);
bool readDistance(std::istream& inputStream, int& value);

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



bool readDistance(std::istream& inputStream, int& value) {
    std::string input;

    if (!std::getline(inputStream, input)) {// legge tutta la riga fino a quando premi Invio e la salva in input
        return false;
    }

    if (input.empty() || input.front() == '-') {
        std::cout << "Input non valido\n";
        return false;
    }

    int parsedValue = 0;//variabile dove inseriremo il valore convertito

    // from_chars converte i caratteri nell'intervallo [inizio, fine)
    // result sarà una struttura con due info: .ec indica l'errore, .ptr dove termina la conversione.
    // Rifiutiamo input non numerici o parziali; se il numero è fuori
    // dall'intervallo di int, impostiamo value al massimo rappresentabile.
    const auto result = std::from_chars(
        input.data(),
        input.data() + input.size(),
        parsedValue
    );

    if (result.ec == std::errc::invalid_argument ||
        result.ptr != input.data() + input.size()) {
        std::cout << "Input non valido\n";
        return false;
        }

    if (result.ec == std::errc::result_out_of_range) {
        value = std::numeric_limits<int>::max();

        std::cout << "Valore troppo grande: impostato a "
                  << value
                  << '\n';

        return true;
    }

    value = parsedValue;
    return true;
}


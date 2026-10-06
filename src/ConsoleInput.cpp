//
// Created by Momo on 23/09/2026.
//

#include "ConsoleInput.h"
#include <iostream>
#include <charconv>
#include <limits>

bool isValid (std::array<Sensor, SENSOR_COUNT>& sensors) {
    int value;
    std::cout << "\n";
    for (int i = 0; i < sensors.size(); i++) {
        std::cout << "Enter "<< sensors[i].getName() << " distance (-1 to exit): ";
        if (!(std::cin >> value)) {
            std::cout << "Input non valido\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            i--;
            continue;
        }
        if (value ==-1) {
            std::cout << "Program terminated\n";
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

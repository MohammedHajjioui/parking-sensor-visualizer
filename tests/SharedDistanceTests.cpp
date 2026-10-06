//
// Created by Momo on 06/10/2026.
//

#include "SharedDistance.h"

#include <array>
#include <cassert>

int main() {
    SharedDistance distance;

    // Verifica dello stato iniziale
    assert(distance.value == 120);
    assert(!distance.hasNewValue);

    // Simulazione della pubblicazione di una nuova misura
    {
        std::lock_guard<std::mutex> lock(distance.mutex);

        distance.value = 50;
        distance.hasNewValue = true;
    }

    // Verifica che la misura sia stata pubblicata
    {
        std::lock_guard<std::mutex> lock(distance.mutex);

        assert(distance.value == 50);
        assert(distance.hasNewValue);
    }

    // Simulazione del consumo da parte della GUI
    int receivedValue = 0;
    bool receivedNewValue = false;

    {
        std::lock_guard<std::mutex> lock(distance.mutex);

        if (distance.hasNewValue) {
            receivedValue = distance.value;
            distance.hasNewValue = false;
            receivedNewValue = true;
        }
    }

    assert(receivedNewValue);
    assert(receivedValue == 50);
    assert(!distance.hasNewValue);

    // Verifica dell'indipendenza tra sensori
    std::array<SharedDistance, 4> distances{};

    {
        std::lock_guard<std::mutex> lock(distances[0].mutex);
        distances[0].value = 20;
        distances[0].hasNewValue = true;
    }

    {
        std::lock_guard<std::mutex> lock(distances[1].mutex);
        distances[1].value = 150;
        distances[1].hasNewValue = true;
    }

    assert(distances[0].value == 20);
    assert(distances[1].value == 150);

    assert(distances[2].value == 120);
    assert(distances[3].value == 120);

    assert(distances[0].hasNewValue);
    assert(distances[1].hasNewValue);
    assert(!distances[2].hasNewValue);
    assert(!distances[3].hasNewValue);
}
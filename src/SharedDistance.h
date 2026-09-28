

#pragma once

#include <mutex>

struct SharedDistance {
    std::mutex mutex;
    int value = 120;
    bool hasNewValue = false;
};
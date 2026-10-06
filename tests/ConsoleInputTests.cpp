//
// Created by Momo on 06/10/2026.
//

#include "ConsoleInput.h"

#include <cassert>
#include <limits>
#include <sstream>

int main() {
    int value = 0;

    {
        std::istringstream input{"50\n"};

        assert(readDistance(input, value));
        assert(value == 50);
    }

    {
        std::istringstream input{"0\n"};

        assert(readDistance(input, value));
        assert(value == 0);
    }

    {
        std::istringstream input{"abc\n"};

        assert(!readDistance(input, value));
    }

    {
        std::istringstream input{"50abc\n"};

        assert(!readDistance(input, value));
    }

    {
        std::istringstream input{"\n"};

        assert(!readDistance(input, value));
    }

    {
        std::istringstream input{"-10\n"};

        assert(!readDistance(input, value));
    }

    {
        std::istringstream input{
            "999999999999999999999999\n"
        };

        assert(readDistance(input, value));
        assert(value == std::numeric_limits<int>::max());
    }

    {
        std::istringstream input{
            "-999999999999999999999999\n"
        };

        assert(!readDistance(input, value));
    }
}
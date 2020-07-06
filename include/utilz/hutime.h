//##############################################################################
//## Project: ClAni ########################### Created by hury on 30.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################


#ifndef CLIANIMATION_HUTIME_H
#define CLIANIMATION_HUTIME_H

#include <chrono>
#include <cstdint>

namespace CliAniHury {

    class HuTime {
        std::chrono::high_resolution_clock _clock;

    public:
        uint64_t millisec() {
            return std::chrono::duration_cast<std::chrono::milliseconds>
                    (_clock.now().time_since_epoch()).count();
        }

        uint64_t microsec() {
            return std::chrono::duration_cast<std::chrono::microseconds>
                    (_clock.now().time_since_epoch()).count();
        }

        uint64_t nanosec() {
            return std::chrono::duration_cast<std::chrono::nanoseconds>
                    (_clock.now().time_since_epoch()).count();
        }
    };
};

#endif //CLIANIMATION_HUTIME_H
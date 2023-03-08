//------------------------------------------------------------------------------
// Throttle.h : class declaration and definition
//------------------------------------------------------------------------------
#pragma once

#include "FuelGauge.h"
#include "Speedometer.h"

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr int FUEL_SLOW = 1;
constexpr int FUEL_MEDIUM = 3;
constexpr int FUEL_FAST = 5;

constexpr int USE_OK = 1;
constexpr int USE_INVALID = 1;

//------------------------------------------------------------------------------
// Throttle : controls FuelGauge and Speedometer
//------------------------------------------------------------------------------
class Throttle {
private: 
    speedSelect speed;

public:
    Throttle() : speed(SPEED_ZERO) { }

    int setThrottle(speedSelect _speed, FuelGauge& fg, Speedometer& spdom) {

        // speed determines fuel use
        switch (_speed) {
        case SPEED_ZERO:
            speed = SPEED_ZERO;
            return true;
        case SPEED_SLOW:
            return fg.useFuel((speed = SPEED_SLOW));
        case SPEED_MEDIUM:
            return fg.useFuel((speed = SPEED_MEDIUM));
        case SPEED_FAST:
            return fg.useFuel((speed = SPEED_FAST));
        default: 
            return fg.getFuelGauge();
        }

        // set speedometer display value
        spdom.setMph(speed);

    }
};


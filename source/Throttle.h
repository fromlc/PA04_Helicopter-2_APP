//------------------------------------------------------------------------------
// Throttle.h : class declaration and definition
//------------------------------------------------------------------------------
#pragma once

#include "FuelGauge.h"
#include "Speedometer.h"

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr int FUEL_ZERO = 0;
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

        int fuelUsed = 0;

        // speed determines fuel use
        switch (_speed) {
        case SPEED_SLOW:
            speed = SPEED_SLOW;
            fuelUsed = FUEL_SLOW;
            break;
        case SPEED_MEDIUM:
            speed = SPEED_MEDIUM;
            fuelUsed = FUEL_MEDIUM;
            break;
        case SPEED_FAST:
            speed = SPEED_FAST;
            fuelUsed = FUEL_FAST;
            break;
        case SPEED_ZERO:
        default:
            speed = SPEED_ZERO;
            fuelUsed = FUEL_ZERO;
        }

        return fg.useFuel(fuelUsed);
        // set speedometer display value
        spdom.setMph(speed);

    }
};


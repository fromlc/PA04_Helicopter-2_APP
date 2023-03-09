//------------------------------------------------------------------------------
// Throttle.h : class declaration and definition
//------------------------------------------------------------------------------
#pragma once

#include "FuelGauge.h"
#include "Speedometer.h"

//------------------------------------------------------------------------------
// Throttle : controls FuelGauge and Speedometer
//------------------------------------------------------------------------------
class Throttle {
private: 
    speedSelect speed;
    int setting;

public:
    Throttle() : speed(SPEED_ZERO), setting(USEFUEL_ZERO) { }

    int getThrottle() const { return (int)setting; }

    int setThrottle(speedSelect _speed, FuelGauge& fg, Speedometer& spdom) {

        // speed determines fuel use
        switch (_speed) {
        case SPEED_SLOW:
            speed = SPEED_SLOW;
            setting = USEFUEL_SLOW;
            break;
        case SPEED_MEDIUM:
            speed = SPEED_MEDIUM;
            setting = USEFUEL_MEDIUM;
            break;
        case SPEED_FAST:
            speed = SPEED_FAST;
            setting = USEFUEL_FAST;
            break;
        case SPEED_ZERO:
        default:
            speed = SPEED_ZERO;
            setting = USEFUEL_ZERO;
        }

        // set speedometer display value
        spdom.setMph(speed);

        return fg.useFuel(setting);

    }
};


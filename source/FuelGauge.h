//------------------------------------------------------------------------------
// FuelGauge.h : class declaration and definition
//------------------------------------------------------------------------------
#pragma once

#include "Speedometer.h"

#include <algorithm>    // max()
using std::max;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr int GAUGE_FULL = 100;     // tank capacity
constexpr int GAUGE_LOW = 15;       // switch to reserve tank

constexpr int USEFUEL_ZERO = 0;
constexpr int USEFUEL_SLOW = 1;
constexpr int USEFUEL_MEDIUM = 3;
constexpr int USEFUEL_FAST = 5;

//------------------------------------------------------------------------------
// FuelGauge
//------------------------------------------------------------------------------
class FuelGauge {
private:
    int fuelLeft;

public:
    // start with full tank
    FuelGauge() : fuelLeft(GAUGE_FULL) { }

    //--------------------------------------------------------------------------
    // - subtracts fuel amount for passed speed
    // - returns max of 0 and fuel amount left
    //--------------------------------------------------------------------------
    int setFuelGauge(speedSelect speed) {

        // speed determines fuel use
        switch (speed) {
        case SPEED_SLOW:
            return useFuel(USEFUEL_SLOW);
        case SPEED_MEDIUM:
            return useFuel(USEFUEL_MEDIUM);
        case SPEED_FAST:
            return useFuel(USEFUEL_FAST);
        }

        return fuelLeft;
    }

    int getFuelGauge() const { return fuelLeft; }

    //--------------------------------------------------------------------------
    // - subtracts passed fuel amount
    // - returns max of 0 and fuel amount left
    //--------------------------------------------------------------------------
    int useFuel(int use) {
        fuelLeft = max(0, fuelLeft - use);
        return fuelLeft;
    }
};


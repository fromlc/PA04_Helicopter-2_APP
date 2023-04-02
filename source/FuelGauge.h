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
constexpr int GAUGE_FULL = 10;      // tank capacity
constexpr int GAUGE_LOW = 15;       // report low fuel
constexpr int GAUGE_RESERVE = 5;    // switch to reserve tank
constexpr int GAUGE_EMPTY = 0;      // crash

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
    // returns units of fuel left
    //--------------------------------------------------------------------------
    int getFuelGauge() const { return fuelLeft; }

    //--------------------------------------------------------------------------
    // - subtracts passed fuel amount
    // - returns max of 0 and fuel amount left
    //--------------------------------------------------------------------------
    int useFuel(int fuel) { 
        fuelLeft -= fuel;
        fuelLeft = max(0, fuelLeft);
        return fuelLeft;
    }

    //--------------------------------------------------------------------------
    // fills fuel tank to capacity, returns units of fuel put in tank
    //--------------------------------------------------------------------------
    int fillFuelTank() {
        int tookFuel = GAUGE_FULL - fuelLeft;
        fuelLeft = GAUGE_FULL;
        return tookFuel;
    }
};


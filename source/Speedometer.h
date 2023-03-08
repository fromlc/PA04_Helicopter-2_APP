//------------------------------------------------------------------------------
// Speedometer.h : class declaration and definition
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
enum speedSelect {
    SPEED_ZERO = 0,
    SPEED_SLOW = 30,
    SPEED_MEDIUM = 65,
    SPEED_FAST = 100,
};

//------------------------------------------------------------------------------
// Speedometer
//------------------------------------------------------------------------------
class Speedometer {
private:
    speedSelect mph;

public: 
    Speedometer() : mph(SPEED_ZERO) { }

    void setMph(speedSelect speed) { mph = speed; }
    speedSelect getMph() const { return mph; }
};


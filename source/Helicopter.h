//------------------------------------------------------------------------------
// Helicopter.cpp : class declaration
//------------------------------------------------------------------------------
#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "Throttle.h"
#include "FuelGauge.h"
#include "Speedometer.h"

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr int HELO_HARDLANDING_LIMIT = -3;

//------------------------------------------------------------------------------
// enum for helicopter status
//------------------------------------------------------------------------------
enum HeloStatus { HELO_ONGROUND, HELO_INAIR, HELO_HARDLANDING, HELO_CRASHED };

//------------------------------------------------------------------------------
// Helicopter
//------------------------------------------------------------------------------
class Helicopter {
private:
	int altitude;
	int distance;
	HeloStatus status;
	Throttle stick;
	FuelGauge fg;
	Speedometer speedo;

public:
	// constructor
	Helicopter();

	// returns current altitude
	int getAltitude() const;
	// returns distance flown so far
	int getDistance() const;
	// puts altitude and distance in reference params
	HeloStatus getPosition(int&, int&);

	// increases altitude by absolute passed value, returns current altitude
	int goUp(int);
	// decreases altitude by absolute passed value, returns current altitude
	int goDown(int);
	// increases distance by absolute passed value, returns distance flown so far
	int goForward(int);
	
	// resets altitude to 0
	void goLand();

	// control enumerated speed
	int setThrottle(speedSelect);
	// get cruising speed in mph
	int getMph() const;
	// get remaining fuel units
	int getFuelLeft() const;
	// get enumerated flight status
	HeloStatus getStatus() const;

private: 
	int _setThrottle(speedSelect);
};
#endif // HELICOPTER_H

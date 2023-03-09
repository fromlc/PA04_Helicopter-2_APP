//------------------------------------------------------------------------------
// Helicopter.cpp : class definition
//------------------------------------------------------------------------------
#include "Helicopter.h"

#include <cstdlib>			// abs()

//------------------------------------------------------------------------------
// constructor
//------------------------------------------------------------------------------
Helicopter::Helicopter() : altitude(0), distance(0), status(HELO_ONGROUND) { }

//------------------------------------------------------------------------------
// returns current altitude
//------------------------------------------------------------------------------
int Helicopter::getAltitude() const { return altitude; }

//------------------------------------------------------------------------------
// returns distance flown so far
//------------------------------------------------------------------------------
int Helicopter::getDistance() const { return distance; }

//------------------------------------------------------------------------------
// puts altitude and distance in reference parameters
//------------------------------------------------------------------------------
HeloStatus Helicopter::getPosition(int& _altitude, int& _distance) {
	_altitude = altitude;
	_distance = distance;

	if (altitude > 0)
		status = HELO_INAIR;
	else if (altitude < HELO_HARDLANDING_LIMIT)
		status = HELO_CRASHED;
	else if (altitude < 0)
		status = HELO_HARDLANDING;
	else if (altitude == 0)
		status = HELO_ONGROUND;

	return status;
}

//------------------------------------------------------------------------------
// - increases altitude by absolute passed value
// - uses fuel amount for medium speed
// - returns current altitude 
//------------------------------------------------------------------------------
int Helicopter::goUp(int incAltitude) {
	fg.useFuel(USEFUEL_MEDIUM);

	status = HELO_INAIR;

	altitude += abs(incAltitude);
	return altitude;
}

//------------------------------------------------------------------------------
// - decreases altitude by absolute passed value
// - uses fuel amount for slow speed
// - returns current altitude 
//------------------------------------------------------------------------------
int Helicopter::goDown(int decAltitude) {
	if (altitude) {
		altitude -= abs(decAltitude);
		fg.useFuel(USEFUEL_SLOW);
	}
	if (altitude < 0) {
		if (altitude < HELO_HARDLANDING_LIMIT) {
			status = HELO_CRASHED;
		}
		else {
			status = HELO_HARDLANDING;
		}
	}
	else {
		status = HELO_INAIR;
	}

	return altitude;
}

//------------------------------------------------------------------------------
// - increases altitude by absolute passed value
// - returns distance flown so far
//------------------------------------------------------------------------------
int Helicopter::goForward(int incDistance) {
	distance += abs(incDistance) * stick.getThrottle();
	return distance;
}

//------------------------------------------------------------------------------
// resets altitude to 0
//------------------------------------------------------------------------------
void Helicopter::goLand() {
	altitude = 0;
	status = HELO_ONGROUND;
}

//------------------------------------------------------------------------------
// - sets enumerated speed
// - returns fuel left
//------------------------------------------------------------------------------
int Helicopter::setThrottle(speedSelect speed) {
	return _setThrottle(speed);
}

//------------------------------------------------------------------------------
// - private
// - sets enumerated speed
// - returns fuel left
//------------------------------------------------------------------------------
int Helicopter::_setThrottle(speedSelect speed) {
	return stick.setThrottle(speed, fg, speedo);
}

//------------------------------------------------------------------------------
// returns cruising speed in mph
//------------------------------------------------------------------------------
int Helicopter::getMph() const { return speedo.getMph(); }

//------------------------------------------------------------------------------
// returns fuel left
//------------------------------------------------------------------------------
int Helicopter::getFuelLeft() const { return fg.getFuelGauge(); }

//------------------------------------------------------------------------------
// returns enumerated flight status
//------------------------------------------------------------------------------
HeloStatus Helicopter::getStatus() const { return status; }

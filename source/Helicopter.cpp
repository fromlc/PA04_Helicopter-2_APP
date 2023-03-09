//------------------------------------------------------------------------------
// Helicopter.cpp : class definition
//------------------------------------------------------------------------------
#include "Helicopter.h"

#include <cstdlib>			// abs()

//------------------------------------------------------------------------------
// constructor
//------------------------------------------------------------------------------
Helicopter::Helicopter() { altitude = distance = 0; }

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
void Helicopter::getPosition(int& _altitude, int& _distance) {
	_altitude = altitude;
	_distance = distance;
}

//------------------------------------------------------------------------------
// - increases altitude by absolute passed value
// - uses fuel amount for medium speed
// - returns current altitude 
//------------------------------------------------------------------------------
int Helicopter::goUp(int incAltitude) {
	altitude += abs(incAltitude);
	fg.useFuel(USEFUEL_MEDIUM);
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
void Helicopter::goLand() { altitude = 0; }

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


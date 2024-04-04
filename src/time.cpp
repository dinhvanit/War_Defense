#include "time.h"



time::time(float setTimeSMax, float setTimeSCurrent) :
	timeSMax(setTimeSMax), timeSCurrent(setTimeSCurrent) {

}



void time::countUp(float dT) {
	if (timeSCurrent < timeSMax) {
		timeSCurrent += dT;
		if (timeSCurrent > timeSMax)
			timeSCurrent = timeSMax;
	}
}


void time::countDown(float dT) {
	if (timeSCurrent > 0) {
		timeSCurrent -= dT;
		if (timeSCurrent < 0)
			timeSCurrent = 0;
	}
}



void time::resetToZero() {
	timeSCurrent = 0;
}


void time::resetToMax() {
	timeSCurrent = timeSMax;
}



bool time::timeSIsZero() {
	return (timeSCurrent <= 0.0f);
}


bool time::timeSIsGreaterThanOrEqualTo(float timeSCheck) {
	return (timeSCurrent >= timeSCheck);
}

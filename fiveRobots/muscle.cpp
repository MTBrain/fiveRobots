#include "muscle.h"

Muscle::Muscle()
{
}

Muscle::Muscle(double _strength, double _cTime, double _eTime, double _cLength, double _eLength, double _time, double _offsetTime)
{
	strength = _strength;
	cTime = cTime;
	eTime = _eTime;
	cLength = _cLength;
	eLength = _eLength;
	time = _time;
	offsetTime = _offsetTime;
}
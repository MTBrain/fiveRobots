#include "muscleclass.h"

MuscleClass::MuscleClass()
{
}

MuscleClass::MuscleClass(double _strength, double _cTime, double _eTime, double _cLength, double _eLength, double _time, double _offsetTime,unsigned int _node1,unsigned int _node2)
{
	strength = _strength;
	cTime = cTime;
	eTime = _eTime;
	cLength = _cLength;
	eLength = _eLength;
	time = _time;
	offsetTime = _offsetTime;
	node1 = _node1;
	node2 = _node2;
}
#include "muscleclass.h"

MuscleClass::MuscleClass()
{
}

MuscleClass::MuscleClass(float _strength, float _cTime, float _eTime, float _cLength, float _eLength, float _time, float _offsetTime,unsigned int _node1,unsigned int _node2)
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
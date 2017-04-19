#include "muscleclass.h"

MuscleClass::MuscleClass()
{
}

MuscleClass::MuscleClass(float _strength, unsigned int _cTime, unsigned int _eTime, float _cLength, float _eLength, unsigned int _time, unsigned int _offsetTime, unsigned int _lastTime, unsigned int _node1, unsigned int _node2, bool _isContracting)
{
	strength = _strength;
	cTime = _cTime;
	eTime = _eTime;
	cLength = _cLength;
	eLength = _eLength;
	time = _time;
	offsetTime = _offsetTime;
	lastTime = _lastTime;
	node1 = _node1;
	node2 = _node2;
	isContracting = _isContracting;
}
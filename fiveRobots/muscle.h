#pragma once
#ifndef _MUSCLECLASS_H_
#define _MUSCLECLASS_H_

class MuscleClass
{
public:
	double strength;
	double cTime, eTime;
	double cLength, eLength;
	double time, offsetTime;

	MuscleClass();

	MuscleClass(double, double, double, double, double, double, double);
};
#endif
#pragma once
#ifndef _MUSCLECLASS_H_
#define _MUSCLECLASS_H_

#define MUSCLE_RELATIVE_SIZE 0.333f
class MuscleClass
{
public:
	double strength;
	double cTime, eTime;
	double cLength, eLength;
	double time, offsetTime;
	unsigned int node1, node2;
	MuscleClass();

	MuscleClass(double, double, double, double, double, double, double,unsigned int,unsigned int);
};
#endif
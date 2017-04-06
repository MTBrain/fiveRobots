#pragma once
#ifndef _MUSCLECLASS_H_
#define _MUSCLECLASS_H_

#define MUSCLE_RELATIVE_SIZE 0.333f
class MuscleClass
{
public:
	float strength;
	float cTime, eTime;
	float cLength, eLength;
	float time, offsetTime;
	unsigned int node1, node2;
	MuscleClass();

	MuscleClass(float, float, float, float, float, float, float,unsigned int,unsigned int);
};
#endif
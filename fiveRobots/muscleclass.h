#pragma once
#ifndef _MUSCLECLASS_H_
#define _MUSCLECLASS_H_

#define MUSCLE_RELATIVE_SIZE 0.333f
class MuscleClass
{
public:
	float strength;
	unsigned int cTime, eTime;
	float cLength, eLength;
	unsigned int time, offsetTime, lastTime;
	unsigned int node1, node2;
	bool isContracting;
	MuscleClass();

	MuscleClass(float, unsigned int, unsigned int, float, float, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, bool);
};
#endif
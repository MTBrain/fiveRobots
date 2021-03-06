#pragma once
#ifndef _CREATURECLASS_H_
#define _CREATURECLASS_H_

#include "nodeclass.h"
#include "muscleclass.h"

class CreatureClass 
{
public:
	NodeClass** nodes;
	MuscleClass** muscles;
	float score;
	int nodeCount;
	int muscleCount;

	CreatureClass();

	CreatureClass(int, int);

	void setScore(float);
};
#endif
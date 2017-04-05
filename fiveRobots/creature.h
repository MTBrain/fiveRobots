#pragma once
#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "node.h"
#include "muscle.h"

class Creature 
{
public:
	Node** nodes;
	Muscle** muscles;
	double score;

	Creature();

	Creature(int, int);

	void setScore(double);
};
#endif
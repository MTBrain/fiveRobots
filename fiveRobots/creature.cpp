#include <stdlib.h>
#include "creatureclass.h"

CreatureClass::CreatureClass()
{
}

CreatureClass::CreatureClass(int n, int m)
{
	nodeCount = n;
	muscleCount = m;
	int i = 0;
	double size, mass, posX, posY, velX, velY;
	double strength, cTime, eTime, cLength, eLength, time, offsetTime;
	for (i = 0; i < n; i++) 
	{
		size = rand() % 10;
		mass = rand() % 10;
		posX = rand() % 10;
		posY = rand() % 10;
		velX = 0;
		velY = 0;
		*nodes[i] = NodeClass(size, mass, posX, posY, velX, velY);
	}

	for (i = 0; i < m; i++)
	{
		strength = rand() % 10;
		cTime = rand() % 10;
		eTime = rand() % 10;
		cLength = rand() % 10;
		eLength = rand() % 10;
		time = rand() % 10;
		offsetTime = 0;
		*muscles[i] = MuscleClass(strength, cTime, eTime, cLength, eLength, time, offsetTime);
	}
}

void CreatureClass::setScore(double _score)
{
	score = _score;
}
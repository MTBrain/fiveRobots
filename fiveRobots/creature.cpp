#include <stdlib.h>
#include "creature.h"

Creature::Creature()
{
}

Creature::Creature(int n, int m)
{
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
		*nodes[i] = Node(size, mass, posX, posY, velX, velY);
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
		*muscles[i] = Muscle(strength, cTime, eTime, cLength, eLength, time, offsetTime);
	}
}

void Creature::setScore(double _score)
{
	score = _score;
}
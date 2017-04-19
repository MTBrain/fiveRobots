#include "creatureclass.h"
#include "fiveRobots.h"
#include <d3dx10math.h>

void applyVelocity(CreatureClass* creature) {
	for (int i = 0; i < creature->nodeCount; i++) {
		if (creature->nodes[i]->posX <= 0.01) {
			float friction = 1 - creature->nodes[i]->size / NODE_MAX_SIZE;
			creature->nodes[i]->velX *= friction;
		}
		creature->nodes[i]->posX += creature->nodes[i]->velX;
		creature->nodes[i]->posY += creature->nodes[i]->velY;
		if (creature->nodes[i]->posY < 0) creature->nodes[i]->posY = 0;
	}
}

void gravity(CreatureClass* creature) {
	for (int i = 0; i < creature->nodeCount; i++) {
		creature->nodes[i]->velY += 9.81 / TICKS_PER_SECOND;
	}
}

void applyMuscle(CreatureClass* creature) {
	for (int i = 0; i < creature->muscleCount; i++) {
		bool isC = creature->muscles[i]->isContracting;
		NodeClass* node1 = creature->nodes[creature->muscles[i]->node1];
		NodeClass* node2 = creature->nodes[creature->muscles[i]->node2];
		D3DXVECTOR2* vector = new D3DXVECTOR2(node1->posX - node2->posX, node1->posY - node2->posY);

		float length = D3DXVec2Length(vector);
		float ceLength = isC ? creature->muscles[i]->cLength : creature->muscles[i]->eLength;
		D3DXVECTOR2* dir;
		D3DXVec2Normalize(dir, vector);
		if (ceLength > length) dir = &(dir->operator*= (-1));

		node1->velX = dir->x * creature->muscles[i]->strength;
		node1->velY = dir->y * creature->muscles[i]->strength;

		dir = &(dir->operator*= (-1));

		node2->velX = dir->x * creature->muscles[i]->strength;
		node2->velY = dir->y * creature->muscles[i]->strength;

	}
}
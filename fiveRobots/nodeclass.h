#pragma once
#ifndef _NODECLASS_H_
#define _NODECLASS_H_
#define NODE_MAX_SIZE 4

class NodeClass
{
public:
	float size; 
	float mass;
	float posX, posY;
	float velX, velY;

	NodeClass();

	NodeClass(float, float, float, float, float, float);
};
#endif
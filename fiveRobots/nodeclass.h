#pragma once
#ifndef _NODECLASS_H_
#define _NODECLASS_H_

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
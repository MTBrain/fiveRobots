#pragma once
#ifndef _NODECLASS_H_
#define _NODECLASS_H_
#define NODE_MAX_SIZE 4

class NodeClass
{
public:
	double size; 
	double mass;
	double posX, posY;
	double velX, velY;

	NodeClass();

	NodeClass(double, double, double, double, double, double);
};
#endif
#pragma once
#ifndef _NODECLASS_H_
#define _NODECLASS_H_

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
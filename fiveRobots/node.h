#pragma once
#ifndef _NODE_H_
#define _NODE_H_

class Node
{
public:
	double size; 
	double mass;
	double posX, posY;
	double velX, velY;

	Node();

	Node(double, double, double, double, double, double);
};
#endif
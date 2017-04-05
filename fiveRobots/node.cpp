#include "node.h"

Node::Node()
{
}

Node::Node(double _size, double _mass, double _posX, double _posY, double _velX, double _velY)
{
	size = _size;
	mass = _mass;
	posX = _posX;
	posY = _posY;
	velX = _velX;
	velY = _velY;
}
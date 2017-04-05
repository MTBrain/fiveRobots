#include "nodeclass.h"

NodeClass::NodeClass()
{
}

NodeClass::NodeClass(double _size, double _mass, double _posX, double _posY, double _velX, double _velY)
{
	size = _size;
	mass = _mass;
	posX = _posX;
	posY = _posY;
	velX = _velX;
	velY = _velY;
}
#include "nodeclass.h"

NodeClass::NodeClass()
{
}

NodeClass::NodeClass(float _size, float _mass, float _posX, float _posY, float _velX, float _velY)
{
	size = _size;
	mass = _mass;
	posX = _posX;
	posY = _posY;
	velX = _velX;
	velY = _velY;
}
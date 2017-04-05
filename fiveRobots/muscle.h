#pragma once
#ifndef _MUSCLE_H_
#define _MUSCLE_H_

class Muscle
{
public:
	double strength;
	double cTime, eTime;
	double cLength, eLength;
	double time, offsetTime;

	Muscle();

	Muscle(double, double, double, double, double, double, double);
};
#endif
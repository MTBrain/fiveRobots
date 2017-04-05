#pragma once

#include "MsgHandlingSystem.h"

class GameClass
{
public:
	GameClass();
	~GameClass();


	bool Frame(MHS);
	vector<MHS>* Initialize(MHS);

private:

	vMHS messages;
	std::vector<unsigned int> loadedObj;

	

};

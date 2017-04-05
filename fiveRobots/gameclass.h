#pragma once

#include "MsgHandlingSystem.h"

class GameClass
{
public:
	GameClass(vMHS*);
	~GameClass();


	bool Frame(void);
	vector<MHS>* Initialize(MHS);

private:

	vMHS* m_vmhs;
	std::vector<unsigned int> loadedObj;

	
};

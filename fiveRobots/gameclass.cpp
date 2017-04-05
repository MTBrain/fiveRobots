#include "gameclass.h"

GameClass::GameClass()
{

}


GameClass::~GameClass()
{

}

vector<MHS>* GameClass::Initialize(MHS in)
{

	
	vector<MHS> re;
	if (loadedObj.size() == 0)
	{
		re.push_back(MHS { 1, 1, sizeof(int) }); // initialize world
	}
	return NULL;
}

bool GameClass::Frame(MHS in)
{
	if (messages.size() != 0)
	{
		return NULL;
	}

	if (in.msg == 0)
	{

	}


	// do shit 

	return true; // should be changed
}

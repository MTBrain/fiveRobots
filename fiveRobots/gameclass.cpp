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
	return &re;
}



bool GameClass::Frame(void)
{
	if (messages.size() != 0)
	{
		return false;
	}



	// do shit 

	return false;; // should be changed
}

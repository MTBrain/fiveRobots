#include "gameclass.h"

GameClass::GameClass(vMHS* in)
{
	m_vmhs = in;
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
	if (m_vmhs->size() != 0)
	{
		return false;
	}



	// do shit 

	return true; // should be changed
}

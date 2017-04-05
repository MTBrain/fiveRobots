#pragma once

#ifndef _MHS_H_
#define _MHS_H_

#define vMHS vector<MHS>
#define MHS_ID_WORLD 0x1

#include <vector>

using namespace std;


struct MHS
{
	unsigned int msg;

	unsigned int ptr;
	unsigned int size;
};

vMHS m_vmhs;
#endif


/*******************************************************************	  	
  ***************            documentary           *****************
  ***************               MHS                *****************
  ******************************************************************


	msg : #-1 ( 0xfff...ff )-> ERROR
			'-> ptr 0x0 -> no message
			'-> ptr -> char* message

		: #0 (0x0) -> unused / no Message / last (end of stream)

		: #1 ( 0x00..01 ) -> game to model and graphic Initialize and Render OBJ 






*/
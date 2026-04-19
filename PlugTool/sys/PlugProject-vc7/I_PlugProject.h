///////////////////////////////////////////////////////////////
//
// I_PlugProject.h                   
// Description:	
//	
///////////////////////////////////////////////////////////////
#pragma once
#include <plug/plug.h>               
//------------------------------------------------------------------------------------------------------------------

struct I_PlugProject
{
	//test Event allow NULL
	virtual bool __stdcall test() = 0;
	//Add interface here
};
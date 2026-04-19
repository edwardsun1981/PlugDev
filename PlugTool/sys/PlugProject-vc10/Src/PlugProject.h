#pragma once
#include "../I_PlugProject.h"

class PlugProject : public I_PlugProject
{
public:
	PlugProject();
	~PlugProject();
private: 
	//---------------------------------------------
	bool __stdcall test();
	
};

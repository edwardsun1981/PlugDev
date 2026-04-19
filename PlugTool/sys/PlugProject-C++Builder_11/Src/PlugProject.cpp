#include "PlugProject.h"

PLUG_COMPONENT_AUTO_REG(PlugProject)//DO NOT EDIT THIS
//------------------------------------------------------------------------------------------------------------------

PlugProject::PlugProject()
{
}

PlugProject::~PlugProject()
{
}

bool __stdcall PlugProject::test()
{
	return true;
}
//------------------------------------------------------------------------------------------------------------------
//C++ builder 链接补丁
extern "C"
{
	off_t _lseek(int fd, off_t offset, int whence)
	{
		return 0;
	}
}
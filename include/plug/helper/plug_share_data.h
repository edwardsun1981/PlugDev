#pragma once
#include "../platform/plug_platform.h"

namespace Plug
{
	struct ShareData
	{
		struct I_App* app = nullptr;
		struct I_PlugModuleMgr* pmm = nullptr;
	};

	inline const char* GetEnvName()
	{
		static std::string name = "_0_DevPlug_" + std::to_string(PlugGetCurrentProcessId());
		return name.c_str();//加进程ID, 为了跟子进程区分
	}

    inline ShareData* GetShareData()
    {
	    static ShareData* sd = nullptr;
	    if (sd)
		    return sd;
		auto buffer = std::getenv(GetEnvName());
		if (buffer)
		{
			sd = (ShareData*)std::atoll(buffer);
			return sd;
		}	
		sd = new ShareData();
		if (!SetEnvVar(GetEnvName(), std::to_string((__int64)sd).c_str()))
			Plug::PlugMessageBox("SetEnvVar failed!");
        return sd;
    }

}

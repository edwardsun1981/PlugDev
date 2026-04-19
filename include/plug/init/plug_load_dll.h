#pragma once
#include "../platform/plug_platform.h"
#include "filesystem.h"
#include <vector>

namespace Plug
{
	//dll load控制类
	class DllLoadController
	{
	public:
		DllLoadController() {};
		~DllLoadController()
		{
			FreeDll();
		}
	public:
		bool LoadDll(std::string filename);
		bool LoadDllAll(std::string dir);
		void FreeDll()
		{
			//现在释放掉所占用的Dll,这里一定要反着卸载,因为加载时是正着的
			for (auto i = m_Handles.size(); i > 0; --i)
				xFreeLibrary(m_Handles[i - 1]);
			m_Handles.clear();
		}
	private:
		std::vector<void*> m_Handles;
	};

	//------------//dll load控制类-------------------------------------------------------------------------------------------
	inline bool DllLoadController::LoadDll(std::string filename)
	{
		void* hInst = xLoadLibrary(filename);
		if (!hInst)
		{
			std::string mess = "Can't load the dll file: ";
			mess += filename;
			PlugMessageBox(mess.c_str());
			return false;
		}
		//保持它在内存中，此类退出时自动释放
		m_Handles.push_back(hInst);
		return true;
	}

	inline bool DllLoadController::LoadDllAll(std::string dir)
	{
		std::vector<std::string> paths;
		FindDll(dir, paths);
		for (size_t i = 0; i < paths.size(); i++)
		{
			LoadDll(paths[i]);
		}
		return true;
	}
}

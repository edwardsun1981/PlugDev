///////////////////////////////////////////////////////////////
// Plug.h
// 建立时间: 2004.8.24
// 作者: 孙华庆		SunHuaQing
// 版本: 2.6 2005.12.13
///////////////////////////////////////////////////////////////
#ifndef	_PLUG_INIT_H_
#define	_PLUG_INIT_H_

#include "plug_load_dll.h"
#include "../helper/plug_module_mgr.h"
#include "../helper/app.h"

namespace Plug
{
	//增加一个路径，可以让dll放到路径里的时候exe能自动找到
	inline void AddDllSupportDir(std::string path)
	{
		std::vector<std::string> subDirs;
		findDir(path, subDirs);
		subDirs.push_back(path);

		for (auto dir : subDirs)
		{
			PlugAddDllDirectory(dir);
		}
	}
	//----------------------------------------------------------------------------------------
	class InitPlug
	{
	private:
		DllLoadController m_control;
		std::vector<Func0> m_release_func;
	public:
		InitPlug(bool load)
		{
			Init(load);
		}
		InitPlug()
		{
			Init();
		}
		~InitPlug()
		{
			for (auto it : m_release_func)//释放DLL之前需要做的清理工作
				it();
			
			m_control.FreeDll();

			Plug::GetApp()->delVal("INIT_PLUG");
		}
		void Init(bool load = true)
		{
			safeGetPMM();//保持在加载dll之前先初始化pmm,保证顺序

			if (Plug::GetApp()->getValPointer("INIT_PLUG"))
				return; //初始化只能一次
			Plug::GetApp()->setValPointer("INIT_PLUG", new int());

			//首先得到本进程的绝对路径
			std::string path = Plug::xGetCurrentPath();
			Plug::AddDllSupportDir(path + "libs\\");
			if(load)
			{
				Load(path);
				Load(path + "dll/");
				Load(path + "plugin/");
				std::vector<std::string> subDirs;
				findDir(path + "plugin/", subDirs);
				for (auto path2 : subDirs)
				{
					Load(path2 + "/");
				}
			}
		}

		void Load(std::string path)
		{
			m_control.LoadDllAll(path);
		}
		void add_release_func(Func0 func)
		{
			m_release_func.push_back(func);
		}
	};
}

#define INIT_PLUG Plug::InitPlug g_init;

#endif	//_PLUG_H_

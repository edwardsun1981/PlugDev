#pragma once
#ifndef	_PLUG_MODULE_MANAGE_H_
#define	_PLUG_MODULE_MANAGE_H_

#include "../platform/plug_platform.h"
#include <unordered_map>
#include <mutex>
//------------------------------------------------------------------------------------------------------------------
namespace Plug
{
	typedef void  (__stdcall* DelInsFunc)(void* p);
	typedef void* (__stdcall* CreateInsFunc)(DelInsFunc& df);

	struct I_PlugModuleMgr
	{
		virtual void __stdcall push(const char* id, CreateInsFunc pNewIns) = 0;
		virtual void __stdcall del(const char* id) = 0;
		virtual bool __stdcall find(const char* id, CreateInsFunc* ppNewIns) = 0;
		virtual void __stdcall AddInstance(void* p, DelInsFunc df) = 0;
		virtual void __stdcall DelInstance(void* p) = 0;
	};

	//plug模块管理类
	class PlugModuleMgr : public I_PlugModuleMgr
	{
	public:
		PlugModuleMgr() {};
		virtual ~PlugModuleMgr() {};
	private:
		//模块存储区
		std::unordered_map<std::string, CreateInsFunc> m_modules;
		//实例存储区
		std::mutex m_instances_mutex;
		std::unordered_map<void*, DelInsFunc> m_instances;//参数1实例，参数2删除实例的函数
	private:
		void __stdcall push(const char* id, CreateInsFunc pNewIns);
		void __stdcall del(const char* id)
		{
			m_modules.erase(id);
		}

		bool __stdcall find(const char* id, CreateInsFunc* ppNewIns);

		void __stdcall AddInstance(void* p, DelInsFunc df);
		void __stdcall DelInstance(void* p);
	};

	//-------------------PlugModuleManage------------------------
	inline void __stdcall PlugModuleMgr::push(const char* id, CreateInsFunc pNewIns)
	{
#ifdef _DEBUG //如果是debug版就检测有同有重复组件
		auto it = m_modules.find(id);
		if (it != m_modules.end())
		{
			std::string mess = "find repeat modules! ID: ";
			mess += id;
			PlugMessageBox(mess.c_str());
		}
#endif
		m_modules[id] = pNewIns;
	}

	inline bool __stdcall PlugModuleMgr::find(const char* id, CreateInsFunc* ppNewIns)
	{
		auto it = m_modules.find(id);
		if (it != m_modules.end())
		{
			*ppNewIns = it->second;
			return true;
		}
		return false;
	}

	//-----------------------------------------------------------
	inline void __stdcall PlugModuleMgr::AddInstance(void* p, DelInsFunc df)
	{
		std::lock_guard<std::mutex> lock(m_instances_mutex);
		m_instances[p] = df;
	}
	inline void __stdcall PlugModuleMgr::DelInstance(void* p)
	{
		DelInsFunc del_fun;
		{
			std::lock_guard<std::mutex> lock(m_instances_mutex);

			auto it = m_instances.find(p);
			if (it == m_instances.end())
				return;

			del_fun = it->second;
			m_instances.erase(it);
		}
		del_fun(p);//所以在这个函数里可能还会调释放组件，这时一定把锁放开
	}

	//--------------------------------------------------
	inline I_PlugModuleMgr* safeGetPMM()
	{
		static I_PlugModuleMgr* pmm = nullptr;
		if (pmm)
			return pmm;
		auto sd = GetShareData();
		if (!sd->pmm)
			sd->pmm = new PlugModuleMgr();//写这里是为了解决debug/release 互相调用问
		pmm = sd->pmm;
		return pmm;
	}
}

#endif
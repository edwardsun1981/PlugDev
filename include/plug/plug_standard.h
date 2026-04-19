#pragma once
#include "platform/plug_platform.h"
#include "helper/plug_share_data.h"
#include "helper/plug_module_mgr.h"

namespace Plug
{
	//-----创建一个组件实例-------------------------------------------------------------------------------
	inline void* PlugCreateInstance(const char* id)
	{
		auto pmm = GetShareData()->pmm;
		if (!pmm)
			return nullptr;

		CreateInsFunc pNewIns = nullptr;
		bool b = pmm->find(id, &pNewIns);
		if (!b)
			return nullptr;
		//创建实例
		DelInsFunc pDelIns = nullptr;
		void* pIns = (void*)pNewIns(pDelIns);
		pmm->AddInstance(pIns, pDelIns);
		return pIns;
	}

	inline void PlugDeleteInstance(void* p)
	{
		auto pmm = GetShareData()->pmm;
		if (!pmm)
			return;
		
		pmm->DelInstance(p);
	}
}

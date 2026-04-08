///////////////////////////////////////////////////////////////
// Plug.h
// 建立时间: 2004.8.24
// 作者: 孙华庆		SunHuaQing
// 版本: 2.7 2025.1.17
// ========================================================================
// Plug 概况
// ========================================================================
// Plug 是一个组件化开发框架，它可以帮助开发人员快速建立组件模块，统一接口和开发规范，
// 方便地创建、释放组件。同时，Plug 规定了程序员开发组件的标准结构，并促使程序员将
// 软件按功能划分为组件，从而形成有助于提高软件开发效率、提高代码重用性、保护源代码、
// 提升软件团队开发沟通速度的规则。支持插件、SDK，Plug 支持 Windows、linux、mac、
// andriod、ios 平台。其他平台未测试，但也应该支持。
// 是软件工程学的具体应用框架。
//
// Plug 如何保护源程序？
// Plug 开发框架使每个程序员只能看到自己编写的源程序，以及自己需要调用的接口，
// 其它源程序，一个字节也不需要知道，当然，除非故意让他知道。
//
//
// Plug 优点
// 二进制兼容，最终编译出的二进制文件可以直接放到其它软件中使用。灵活的二进制输出形式，
// 可以在不改动任何源码的情况下，把无数个组件编译成一个可执行文件，或把任意多个组件
// 编译成任意多个(.DLL, .so)。也就是说，最终要 Release 的程序，无论开发时用了多少组件
// (.DLL, .so)，发布时都可以只有一个可执行体 EXE，也可以带任意多个(.DLL, .so)，可以
// 随意定制。
//
// Plug 特点
// 1、不需要引出函数
// 2、不需要CPP文件，任何类型的程序只需要包含盘plug.h就可以使用
// 3、只需要一句初始化语句，不需要手动释放
// 4、使用更简单，请见 Plug 使用原则
//
//
//
// Plug 使用原则:
//
// 1、标准 Plug dll，直接使用
// 2、EXE，在任何全局的地方调用一下 INIT_PLUG
// 3、Dll(win32 dll、mfc dll、ocx dll、atl dll、DSFilter dll...)，在全局加一句
//    PLUG_COMPONENT_AUTO_REG(ProjectName) 就可以像标准 Plug dll 中一样使用了
//
// 4、所有标准 Plug dll 可以编译到一个 Dll，或可以和其中一个 EXE 编译到一个 EXE 文件里
// 5、编译选项，如果能在源文件中修改，就不要在编译选项中修改。如数据对齐，默认 4 字节，
//    如果要修改成其它字节，请在文件中修改；如果修改了编译选项，请在本文件中说明，以供
//    联编时参照
// 6、Dll 出现在本目录或 PlugDll 目录及子目录中时，将会在 EXE 初始化时被 load。
//    PlugDll 目录及子目录中只能放 Dll 文件
//
// 开发原则 :
//
//
// Plug 实现原理 :
//
///////////////////////////////////////////////////////////////
#ifndef	_PLUG_H_
#define	_PLUG_H_
#include "plug_standard.h"
#include "helper/app.h"
#include "helper/log.h"
#include "init/init.h"
#include <fstream>

namespace Plug
{
	inline void debug_check(const char* id)
	{
#ifdef _WINDOWS_
		static bool find_release = false;
		if (find_release)
			return;

		//查找release.txt,
		std::wstring path = xGetCurrentPath3();
		path += L"release.txt";
		std::wfstream fs;
		fs.open(path);
		if (fs.is_open())
		{
			find_release = true;
			//找到了
			std::string mess = "这是一个debug dll, 却发现了 release.txt!, 这是不是应该用release版呀？ 组件ID: ";
			mess += id;
			mess += ", 是否继续？";
			if (IDYES != MessageBoxW(GetActiveWindow(), c2w(mess).c_str(), L"Plug Message!", MB_YESNO | MB_ICONWARNING))
				Plug::TerminateProc();
		}
#endif
	}

	template <typename T>
	void __stdcall DelProject(void* p)
	{
		delete (T*)p;
	}

	template <typename T>
	void* __stdcall NewProject(DelInsFunc& df)
	{
		df = DelProject<T>;
		return new T();
	}

	//组件自动注册模块
	template <typename T>
	class AutoReg
	{
	public:
		AutoReg(const char* id) 
		{
			auto pmm = safeGetPMM();
			pmm->push(id, NewProject<T>);

#ifdef _DEBUG//检测debug
			debug_check(id);//如果是debug版就检测,是否release.txt
#endif
			m_id = id;
		}
		~AutoReg()
		{
			auto pmm = safeGetPMM();
			pmm->del(m_id.c_str());
		}
	private:
		std::string m_id;
	};
}

//------------------------------------------------------------------------------------------------------------------

////创建一个组件
#define NEW(ProjectName) (struct I_##ProjectName*)(Plug::PlugCreateInstance(#ProjectName))
#define DEL(instance) Plug::PlugDeleteInstance(instance)

#define NEWSP(ProjectName) std::shared_ptr<I_##ProjectName>(NEW(ProjectName), Plug::PlugDeleteInstance)

//所有组件通用代码写成宏
//-----------------自动注册模块信息-----------
#define PLUG_COMPONENT_AUTO_REG(ProjectName) Plug::AutoReg<ProjectName> g_autoReg##ProjectName(#ProjectName);

//-----------------------组件作为单件--------------------------------------------------------

inline void delSingleton(const char* _name)
{
	Plug::GetApp()->delVal(_name);
}
inline void* getSingleton(const char* _name)
{
	return Plug::GetApp()->getValPointer(_name);
}

#define GetPlug(PlugName) ((I_##PlugName*)getSingleton(#PlugName))//注意，GetPlug是获取的单例， 进程内必要有地方SetPlug， 否则GetPlug会返回nullptr.如果不是单例，请直接使用NEW(PlugName)创建实例。
inline void SetPlug(const char* _name, void* _plug)// 约束，第二参数所指对象必须保证释放前delPlug
{
	Plug::GetApp()->setValPointer(_name, _plug);
}
#endif	//_PLUG_H_
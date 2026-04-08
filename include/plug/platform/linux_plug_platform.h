///////////////////////////////////////////////////////////////
// 建立时间: 2005.12.27
// 此文件定义一些平台相关的东西
///////////////////////////////////////////////////////////////
#ifndef	_WIN_PLUG_PLATFORM_H_
#define	_WIN_PLUG_PLATFORM_H_

#include <unistd.h> //为了 getcwd
#include <string>
#include <vector>
#include <dlfcn.h> //dlopen
#include <string.h> //兼容linux strcpy
#include <signal.h> //kill用
#include <stdio.h>
#include <thread>
#include <pthread.h>//set thread name
#include <iostream> //app xcode 的strcpy 需要
#ifndef __stdcall
#define __stdcall
#endif

#ifdef __APPLE__
	#ifndef _HAS_CXX17 //xcode for macos 不知道如何判断，先强制使用17以上吧
		#if __cplusplus >= 201703L
			#define _HAS_CXX17 1
		#endif		
	#endif
#endif
#ifdef __EMSCRIPTEN__ //emscripten .wasm C++编译器
	#if __cplusplus >= 201703L
		#define _HAS_CXX17 1
	#endif
#endif

#ifndef __int64
typedef	long long __int64;
#endif // !__int64

//-------------------------------------------------------------------------------------------------------------

#ifdef __ANDROID__
#include <android/log.h>
#endif

#include <locale> //用于utf8->wchar_t字符转换
#include <codecvt>//用于utf8->wchar_t字符转换

namespace Plug
{
	inline int PlugGetCurrentProcessId()
	{
		return getpid();
	}
	inline void PlugMessageBox(const char* mess)
	{
#ifdef __ANDROID__
		__android_log_print(ANDROID_LOG_INFO, "PlugMessageBox", mess);
#endif
		printf("\r\n PlugMessageBox: ");
		printf("%s", mess);
		printf("\r\n");
	}
	inline void PlugMessageBox(const wchar_t* mess)
	{
	}
	inline bool PlugMessageBoxYN(const wchar_t* mess)
	{
		return false;
	}
	inline std::wstring c2w(std::string str)//GBK to unicode
	{
		return L"";
	}
	inline void* xLoadLibrary(std::string lpLibFileName)
	{
//#ifdef __Custom_IOS__//云游戏客户端的优酷SDK  IOS版本 对接不准用dlopen
//		return nullptr;
//#else
		return dlopen(lpLibFileName.c_str(), RTLD_LAZY);
//#endif
	}

	inline bool xFreeLibrary(void* hLibModule)
	{
//#ifdef __Custom_IOS__//云游戏客户端的优酷SDK  IOS版本 对接不准用dlopen
//#else
		dlclose(hLibModule);
//#endif
		return true;
	}

	inline std::string xGetCurrentPath()
	{
		std::string s = getcwd(nullptr, 0);
		s += "/";
		return s;
	}
	inline std::wstring u8_2w(std::string str)//utf8 to unicode
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.from_bytes(str);
	}
	inline std::string w2u8(std::wstring str)//unicode to utf8
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(str);
	}
	inline std::string gbk2u8(std::string str)
	{
		return str;
	}
	inline std::string u8_2gbk(std::string str)
	{
		return str;
	}
	inline void TerminateProc()
	{
		kill(Plug::PlugGetCurrentProcessId(), SIGKILL);
	}
	inline void SetThreadName(const char* t_name)
	{
#ifdef __APPLE__// xcode for macos 编译不过，不知道为啥
        return ;
#else
		pthread_setname_np(pthread_self(), t_name);
#endif
	}
	inline void PlugAddDllDirectory(std::string path){}

	inline bool SetEnvVar(const char* name, const char* var)
	{
		return setenv(name, var, 1) == 0;
	}

}

#endif

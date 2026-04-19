///////////////////////////////////////////////////////////////
// 建立时间: 2005.12.27
// 此文件定义一些平台相关的东西
///////////////////////////////////////////////////////////////
#ifndef	_WIN_PLUG_PLATFORM_H_
#define	_WIN_PLUG_PLATFORM_H_

#include <windows.h>
#pragma warning(disable: 4996)//strcpy 警告
#pragma warning(disable: 4819) //文件编码警告
#pragma warning(disable: 4267) //size_t 转 int警告
#include <vector>
#include <string>

#ifndef _WINDOWS_
#define _WINDOWS_
#endif
//-------------------------------------------------------------------------------------------------------------
namespace Plug
{
	inline std::string wchar_2_char(std::wstring str, int type)//unicode to utf8
	{
		size_t len = WideCharToMultiByte(type, 0, (const wchar_t*)str.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::vector<char> tempBuff(len + 1);
		char* szUtf8 = &tempBuff[0];//(char*)malloc(len + 1);
		memset(szUtf8, 0, len + 1);
		WideCharToMultiByte(type, 0, (const wchar_t*)str.c_str(), -1, szUtf8, (int)len, nullptr, nullptr);
		std::string sRet = szUtf8;
		return sRet;
	}
	inline std::wstring char_2_wchar(std::string str, int type)//utf8 to unicode
	{
		size_t len = MultiByteToWideChar(type, 0, str.c_str(), -1, nullptr, 0);
		std::vector<wchar_t> tempBurr(len + 1);
		wchar_t* wszGBK = &tempBurr[0];//new wchar_t[len + 1];
		memset(wszGBK, 0, (len + 1) * sizeof(wchar_t));
		MultiByteToWideChar(type, 0, (LPCSTR)str.c_str(), -1, wszGBK, (int)len);
		std::wstring sRet(wszGBK);
		return sRet;
	}

	inline std::string w2c(std::wstring str)//unicode to GBK
	{
		return wchar_2_char(str, CP_ACP);
	}
	inline std::wstring c2w(std::string str)//GBK to unicode
	{
		return char_2_wchar(str, CP_ACP);
	}
	inline std::string w2u8(std::wstring str)//unicode to utf8
	{
		return wchar_2_char(str, CP_UTF8);
	}
	inline std::wstring u8_2w(std::string str)//utf8 to unicode
	{
		return char_2_wchar(str, CP_UTF8);
	}
	inline std::string gbk2u8(std::string str)
	{
		return w2u8(c2w(str));
	}
	inline std::string u8_2gbk(std::string str)
	{
		return w2c(u8_2w(str));
	}

	inline void PlugMessageBox(const char* mess)
	{
#if defined __BORLANDC__ //C++ builder 对 u8""不起作用，还是GKB
		MessageBoxW(GetActiveWindow(), c2w(mess).c_str(), L"Plug Message!", MB_OK | MB_ICONWARNING);
		return;
#endif
		MessageBoxW(GetActiveWindow(), u8_2w(mess).c_str(), L"Plug Message!", MB_OK | MB_ICONWARNING);
	}

	inline DWORD PlugGetCurrentProcessId()
	{
		return GetCurrentProcessId();
	}

	//-------------------------------------------
	inline std::wstring xGetCurrentPath3()
	{
		wchar_t base_path[260] = { 0 };
		GetModuleFileNameW(nullptr, base_path, 260);
		std::wstring path = base_path;
		path = path.substr(0, path.rfind(L'\\') + 1);
		return path;
	}
	inline std::string xGetCurrentPath()
	{
		return w2u8(xGetCurrentPath3());
	}
	inline std::string xGetCurrentPath2()
	{
		return w2c(xGetCurrentPath3());
	}
	inline void* xLoadLibrary(std::string fileName)
	{
		std::wstring path = u8_2w(fileName);
		auto h = LoadLibraryW(path.c_str());
		if (h)
			return h;
		h = ::LoadLibraryExW(path.c_str(), nullptr, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS); // LOAD_LIBRARY_SEARCH_DEFAULT_DIRS 配合AddDllDirectory参考注释
		if (h)
			return h;
		h = ::LoadLibraryExW(path.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
		return h;
	}

	inline bool xFreeLibrary(void* hLibModule)
	{
		return !!FreeLibrary((HMODULE)hLibModule);
	}
	inline void TerminateProc()
	{
		TerminateProcess(GetCurrentProcess(), 0);
	}
	inline void SetThreadName(const char* threadName)
	{
		auto name = u8_2w(threadName);
		//SetThreadDescription(GetCurrentThread(), name.c_str());//这个API win7早期版本还不支持，需要的时候打开吧，默认注释掉
	}
	inline void PlugAddDllDirectory(std::string path)
	{
		auto hr = AddDllDirectory(u8_2w(path).c_str());
	}
	inline bool SetEnvVar(const char* name, const char* var)
	{
		return _putenv_s(name, var) == 0;//SetEnvironmentVariableA(name, var); // 
	}
}

#endif

///////////////////////////////////////////////////////////////
// 建立时间: 2005.12.27
// 此文件定义一些平台相关的东西
///////////////////////////////////////////////////////////////
#ifndef	_UNREAL_PLUG_PLATFORM_H_
#define	_UNREAL_PLUG_PLATFORM_H_

#pragma warning(disable: 4996)//strcpy 警告
#pragma warning(disable: 4819) //文件编码警告
#pragma warning(disable: 4265) //类包含虚函数，但其不常用的析构函数不是虚函数；该类的实例可能无法进行正确析构 警告

#include <locale.h>
#include <codecvt>
#include <vector>
#include <Containers/StringConv.h> //用于utf8跟wchar之间转换
//-------------------------------------------------------------------------------------------------------------
//auto path = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
namespace Plug
{
	inline std::string w2c(std::wstring str)//unicode to GBK
	{
		std::wstring_convert<std::codecvt<wchar_t, char, mbstate_t>> converter(new std::codecvt<wchar_t, char, mbstate_t>("CHS"));
		std::string str2 = converter.to_bytes(str);
		return str2;

	}
	inline std::wstring c2w(std::string str)//GBK to unicode
	{
		std::wstring_convert<std::codecvt<wchar_t, char, mbstate_t>> converter(new std::codecvt<wchar_t, char, mbstate_t>("CHS"));
		std::wstring wstr1 = converter.from_bytes(str);
		return wstr1;
	}
	inline std::string w2u8(std::wstring str)//unicode to utf8
	{
		return TCHAR_TO_UTF8(WCHAR_TO_TCHAR(str.c_str()));
	}
	inline std::wstring u8_2w(std::string str)//utf8 to unicode
	{
		return TCHAR_TO_WCHAR(UTF8_TO_TCHAR(str.c_str()));
	}

	inline std::wstring u8_u16(std::string& str)//utf8 to unicode
	{
		std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
		std::u16string wide_str = convert.from_bytes(str);//utf8 ת wchar_t*

		std::wstring wstr = (const wchar_t*)wide_str.c_str();
		return wstr;
	}
	inline std::wstring u8_u16(const char* str)//utf8 to unicode
	{
		std::string str2 = str;
		return u8_u16(str2);
	}
	//-------------------------------------------
	
	inline int PlugGetCurrentProcessId()
	{
		return FPlatformProcess::GetCurrentProcessId();
	}

	inline void PlugMessageBox(const char* mess)
	{
	}
	inline std::string xGetCurrentPath()
	{
		auto path = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
		path += "Binaries/Win64/";
		return Plug::w2u8(*path);
	}

	inline void* xLoadLibrary(std::string fileName)
	{
		return FPlatformProcess::GetDllHandle(u8_2w(fileName).c_str());
	}

	inline bool xFreeLibrary(void* hLibModule)
	{
		FPlatformProcess::FreeDllHandle(hLibModule);
		return true;
	}

	//------------------------------------------------------------
	inline std::string gbk2u8(std::string str)
	{
		return Plug::w2u8(Plug::c2w(str));
	}
	inline std::string u8_2gbk(std::string str)
	{
		return Plug::w2c(Plug::u8_2w(str));
	}
	inline void TerminateProc()
	{
		auto h = FPlatformProcess::OpenProcess(FPlatformProcess::GetCurrentProcessId());
		FPlatformProcess::TerminateProc(h, true);
	}

	inline bool SetEnvVar(const char* name, const char* var)
	{
		FPlatformMisc::SetEnvironmentVar(u8_u16(name).c_str(), u8_u16(var).c_str());
		return true;
	}
	inline void SetThreadName(const char*) {}
	inline void PlugAddDllDirectory(std::string path)
	{
		FPlatformProcess::AddDllDirectory(u8_2w(path).c_str());
	}
}

#endif

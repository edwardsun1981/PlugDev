///////////////////////////////////////////////////////////////
// 建立时间: 2021.10.15
// 此文件 windows 和UE文件和文件夹遍历
///////////////////////////////////////////////////////////////
#ifndef	_WIN_FILESYSTEM_H_
#define	_WIN_FILESYSTEM_H_

#include <string>
#if _HAS_CXX17
#include <iostream>
#include <filesystem>
#else
#include <io.h> //遍历文件findfirst
#endif
//-------------------------------------------------------------------------------------------------------------
namespace Plug
{
	inline void FindDll(std::string dir, std::vector<std::string>& paths)
	{
#if _HAS_CXX17
		auto dir2 = std::filesystem::u8path(dir);
		if (!std::filesystem::exists(dir2))
			return;
		for (auto& entry : std::filesystem::directory_iterator(dir2))
		{
			if (!entry.is_directory() && entry.is_regular_file())
			{
				auto ext = entry.path().extension().string();
				if (ext == ".dll" || ext == ".so")
				{
					auto u8s = entry.path().u8string();
					paths.push_back((char*)u8s.c_str());
				}
			}
		}
#else   //现在UE还不支持_HAS_CXX17, c++ builder 12已经支持0x17,但对上面代码兼容性差,无法编译通过,所以下面代码还有必要保留
		_finddata_t fileinfo;
		auto hand = _findfirst(Plug::u8_2gbk(dir + "*.dll").c_str(), &fileinfo);
		if (hand == -1L)
			return;
		for (;;)
		{
			paths.push_back(dir + Plug::gbk2u8(fileinfo.name));
			if (_findnext(hand, &fileinfo) != 0)
				break;
			//file.name;
		}
		_findclose(hand);
#endif

	}
	//增加一个路径，可以让dll放到路径里的时候exe能自动找到
	inline void findDir(std::string path, std::vector<std::string>& subDirs)
	{
#if _HAS_CXX17
		auto dir2 = std::filesystem::u8path(path);
		if (!std::filesystem::exists(dir2))
			return;

		for (auto& entry : std::filesystem::directory_iterator(dir2))
		{
			if (entry.is_directory())
			{
				auto u8s = entry.path().u8string();
				subDirs.push_back((char*)u8s.c_str());
			}
		}
#else
		auto str = Plug::u8_2gbk(path + "*");
		_finddata_t fileinfo;
		auto hand = _findfirst(str.c_str(), &fileinfo);
		if (hand == -1L)
			return;

		for (;;)
		{
			if (fileinfo.attrib & _A_SUBDIR)
			{
				if (fileinfo.name[0] != '.')// filter the '..' and '.' in the path
					subDirs.push_back(path + Plug::gbk2u8(fileinfo.name));
			}

			if (_findnext(hand, &fileinfo) != 0)
				break;
		}
		_findclose(hand);
#endif
	}

}

#endif

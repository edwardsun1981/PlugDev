#pragma once
#include "..\I_Tool.H"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
//这是具体实现接口的类，可以在这里加一些注释

class Tool : public I_Tool
{
public:
    Tool();
    ~Tool();
private:
    //创建一个工程
    //name工程名称，工程路径
    //type工程类型
    //支持main test
    //支持gui test
    //支持winmain test
    bool __stdcall MakeProject(char* name, char* path, ProjectType type, bool main, bool winmain);
    bool __stdcall setupVCpath();
    bool AddProjPath(std::string path, std::string tar_path);

    //复制文件
    bool copy_file(const char* name, char* path, std::string PlugProjectDir, ProjectType type);
private:
    std::vector<std::string> m_FilePath;
    std::string m_prj_name;
    bool m_main;
    bool m_winmain;
};

//文件字符串替换函数
//SrcFile要进行处理的文件//rep将被替掉的字符串//替换成的串
bool FileStrReplace(const char* SrcFile, std::string rep, std::string tar);
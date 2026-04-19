#include "Tool.h"
//----------------------------自动注册模块信息---------------------------
PLUG_COMPONENT_AUTO_REG(Tool);

//------------------Tool-----------------------
Tool::Tool()
{
}
Tool::~Tool()
{
}
bool FileExist(std::string f)
{
    return std::filesystem::exists(std::filesystem::path(f));
};
bool chkDirExist(std::string path)
{
    return std::filesystem::exists(std::filesystem::path(path));
}
void chkDirAndCreate(std::string path)
{
    if (!chkDirExist(path))
    {
        CreateDirectoryA(path.c_str(), NULL);
    }
}

bool __stdcall Tool::setupVCpath()
{
	std::string src = Plug::GetCurrentPath();
	src += "sys\\Microsoft.Cpp.x64.user.props";

    char name[128] = { 0};
    DWORD size = 128;
    GetUserNameA(name, &size);
    std::string path = "C:\\Users\\";
    path += name;
    path += "\\AppData\\Local";
    chkDirAndCreate(path);
    path += "\\Microsoft";
    chkDirAndCreate(path);
    path += "\\MSBuild";
    chkDirAndCreate(path);
    path += "\\v4.0";
    chkDirAndCreate(path);

	std::string t2 = path;
	t2 += "\\Microsoft.Cpp.x64.user.props";
	if (FileExist(t2))
		return true;//已经存在，无需配置

	BOOL b = CopyFileA(src.c_str(), t2.c_str(), false);
	if (!b)
	{
		std::string str = "无法复制文件： ";
		str += src;
		str += " 到: ";
		str += t2;

		MessageBoxA(GetActiveWindow(), path.c_str(), "复制文件出错!", 0);
		return false;
	}

    std::string includ_path = Plug::GetCurrentPath();
    includ_path = includ_path.substr(0, includ_path.size() - 9);
    includ_path += "include";

    return FileStrReplace(t2.c_str(), "plug_path_", includ_path);
    //int a = 0;
    //chkDirAndCreate("d:\\temp2");
}

//创建一个工程
//name工程名称，工程路径
bool __stdcall Tool::MakeProject(char* name, char* path, ProjectType type, bool main, bool winmain)
{
    m_main = main;
    m_winmain = winmain;

    m_prj_name = name;
    //参数检查
    std::string propath = path;
    int sl = (int)propath.length();
    if (propath[sl - 1] != '\\')
    {
        propath += "\\";
    }
    std::string str;

    //std::string PlugProjectDir = Plug::GetCurrentPath();
    std::string PlugProjectDir = "sys\\";
    if (type == Project_vc6)
    {
        str = "PlugProject-vc6\\";
    }
    if (type == Project_vc7_1)
    {
        str = "PlugProject-vc7\\";
    }
    if (type == Project_vc8)
    {
        str = "PlugProject-vc8\\";
    }
    if (type == Project_vc9)
    {
        str = "PlugProject-vc9\\";
    }
    if (type == Project_vc10)
    {
        str = "PlugProject-vc10\\";
    }
    if (type == Project_vc11)
    {
        str = "PlugProject-vc11\\";
    }
    if (type == Project_vc12)
    {
        str = "PlugProject-vc12\\";
    }
    if (type == Project_vs2015)
    {
        str = "PlugProject-vs2015\\";
    }
    if (type == Project_vs2017)
    {
        str = "PlugProject-vs2017\\";
    }
    if (type == Project_vs2019)
    {
        str = "PlugProject-vs2019\\";
    }
    if (type == Project_vs2022)
    {
        str = "PlugProject-vs2022\\";
    }
    if (type == Project_bcb2006)
    {
        str = "PlugProject-bcb2006\\";
    }
    if (type == Project_bcb6)
    {
        str = "PlugProject-bcb6\\";
    }
    if (type == Project_cb2009)
    {
        str = "PlugProject-cb2009\\";
    }
    if (type == Project_cb2010)
    {
        str = "PlugProject-cb2010\\";
    }
    if (type == Project_cbxe2)
    {
        str = "PlugProject-cbxe2\\";
    }
    if (type == Project_cbxe10)
    {
        str = "PlugProject-cbxe10\\";
    }
    if (type == Project_cb10_berlin)
    {
        str = "PlugProject-C++Builder_10_berlin\\";
    }
	if (type == Project_cb11)
	{
		str = "PlugProject-C++Builder_11\\";
	}
    if (type == Project_cb12)
    {
        str = "PlugProject-C++Builder_12\\";
    }
    if (type == Project_xcode)
    {
        str = "PlugProject xcode\\";
    }
    if (type == Project_code_block)
    {
        str = "PlugProject-code_block\\";
    }
    if (type == Project_vs2019_linux)
    {
        str = "PlugProject-vs2019_linux\\";
    }
    PlugProjectDir += str;
    AddProjPath(str, std::string() + path + name + "\\");

    if (!copy_file(name, path, PlugProjectDir, type))
        return false;
    return true;
}

bool Tool::AddProjPath(std::string path, std::string tar_path)
{
    auto AddFolder = [this](std::string SrcPath, std::string path)
    {
        auto FindFile = [](std::string dir, bool child, std::vector<std::string>& paths)
        {
            for (auto& entry : std::filesystem::directory_iterator(dir))
            {
                if (!entry.is_directory() && entry.is_regular_file())
                {
                    paths.push_back(entry.path().filename().u8string());
                }
            }
        };

        std::vector<std::string> paths;
        
        FindFile(SrcPath + path, false, paths);
		if (path.size() > 0)
			path += "\\";
        for (size_t i = 0; i < paths.size(); i++)
        {
            m_FilePath.push_back((path + paths[i]));
        }
    };

    std::string src = Plug::GetCurrentPath();
    src += "sys\\";
    src += path;

    std::string tar = tar_path;
    chkDirAndCreate(tar);

    AddFolder(src, "");//接口目录

    AddFolder(src, "Dll");
    chkDirAndCreate(tar + "Dll");
    AddFolder(src, "Src");
    chkDirAndCreate(tar + "Src");
    if (m_main)
    {
        AddFolder(src, "Test");
        chkDirAndCreate(tar + "Test");
    }
    if (m_winmain)
    {
        AddFolder(src, "WinTest");
        chkDirAndCreate(tar + "WinTest");
    }
    //如果是xcode 特殊处理
    if (FileExist(src + "Dll\\PlugProject.xcodeproj"))
    {
        AddFolder(src, "Dll\\PlugProject.xcodeproj");
        std::string xcode_path = "Dll\\" + m_prj_name + ".xcodeproj";
        chkDirAndCreate(tar + xcode_path);

        if (m_main)
        {
            AddFolder(src, "Test\\Test.xcodeproj");
            chkDirAndCreate(tar + "Test\\Test.xcodeproj");
        }
    }

    return true;
}
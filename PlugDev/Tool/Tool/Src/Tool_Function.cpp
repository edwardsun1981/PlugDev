#include "Tool.h"

//字符串替换函数
//src要进行处理的字符串//rep将被替掉的字符串//替换成的串
void replace(std::string* src, std::string rep, std::string tar)
{
    int i = (int)src->find(rep);
    while (i != -1)
    {
        src->replace(i, rep.size(), tar);
        i = (int)src->find(rep);
    }
}

#include <istream>

//文件字符串替换函数
//SrcFile要进行处理的文件//rep将被替掉的字符串//替换成的串
bool FileStrReplace(const char* SrcFile, std::string rep, std::string tar)
{
    std::wstring ss = Plug::c2w(SrcFile);
    std::ifstream from(Plug::c2w(SrcFile), std::ifstream::in | std::ifstream::binary);
    if (!from)
        return false;

    std::vector<char> tmp;
    tmp.resize(256 * 1024);
    char* str = &tmp[0];
    from.read(str, tmp.size());

    std::string src = str;
    std::string tmp1 = Plug::u8_2gbk(src);
    replace(&src, rep, tar);

    from.close();
    std::ofstream to(Plug::c2w(SrcFile), std::ios_base::out | std::ifstream::binary | std::ios_base::trunc);
    to.write(src.c_str(), src.size());
    std::string tmp2 = Plug::u8_2gbk(src);
    to.close();
    return true;
}

//复制文件
bool Tool::copy_file(const char* name, char* path, std::string PlugProjectDir, ProjectType type)
{
    //目录建立完成，现在开始复制文件
    auto mypath = Plug::GetCurrentPath();

    for (int i = 0; i < m_FilePath.size(); i++)
    {
        std::string src = PlugProjectDir;
        std::string ProjectPath = path;
        ProjectPath += name;
        ProjectPath += "\\";
        std::string tar = ProjectPath;

        src += m_FilePath[i];
        tar += m_FilePath[i];
        std::string t = tar;
        replace(&t, "PlugProject", name);
        std::string dir = mypath;
        dir += src;
        BOOL b = CopyFileA(dir.c_str(), t.c_str(), false);
        if (!b)
        {
            std::string str = "无法复制文件： ";
            str += t;

            MessageBoxA(GetActiveWindow(), str.c_str(), "复制文件出错!", 0);
            return false;
        }
        if (t[t.length() - 1] == 'o' && t[t.length() - 2] == 'c' && t[t.length() - 3] == 'i')
        {
            continue;//特殊类型文件,无需替换字符串
        }
        if (t[t.length() - 1] == 's' && t[t.length() - 2] == 'e' && t[t.length() - 3] == 'r')
        {
            continue;
        }
        //替换文件中的项目名称
        std::string name1 = Plug::gbk2u8(name);
        FileStrReplace(t.c_str(), "PlugProject", name1);
    }
    return true;
}

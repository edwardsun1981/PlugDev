//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"

#include <string>
#include <vector>
#include <stdio.h>
#include <Filectrl.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1* Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject* Sender)
{
    ComboBox1->ItemIndex = Project_vs2022;

	std::string str = Plug::GetCurrentPath();

    str += "sys\\Dir.ini";
	FILE* file = fopen(str.c_str(), "r");
    if (file)
    {
		char path[256];
		path[0] = '\0';

        fread(path, 1, 256, file);
		fclose(file);
		Edit2->Text = path;
	}
}
//---------------------------------------------------------------------------
bool TForm1::SelectDir2(std::wstring Caption, std::string& Dir)
{
#define PATH_MAX_LENGTH 260 //WIN7最长260
    //使用wchar系列的API，以适应中文环境

	wchar_t PathBuf[PATH_MAX_LENGTH] = {0};
	BROWSEINFOW bi;
	memset(&bi, 0x00, sizeof(bi));

    bi.hwndOwner = this->Handle;
    bi.pidlRoot =  NULL;  // 没有使用Root参数
    bi.pszDisplayName = PathBuf;
    bi.lpszTitle = Caption.c_str();
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.lpfn = 0;

    LPITEMIDLIST pidl = SHBrowseForFolderW(&bi);

    if (pidl)
    {
		SHGetPathFromIDListW(pidl, PathBuf);

		Dir = Plug::w2c(PathBuf);
        return true;
	}
    return false;
}


void __fastcall TForm1::Button2Click(TObject* Sender)
{
    std::string Dir;

    bool b = SelectDir2(L"Please select a directory...", Dir);//Options
    if (b)
    {
        if (Dir[Dir.size() - 1] != '\\')
        {
            Dir += "\\";
        }
        Edit2->Text = Dir.c_str();
    }

	Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject* Sender)
{
    make_project();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormShow(TObject* Sender)
{
    this->DoubleBuffered = true;
}
//---------------------------------------------------------------------------

#include "Unit2.h"
void __fastcall TForm1::Button3Click(TObject* Sender)
{
    TAbout* about = new TAbout(this);
    about->ShowModal();
    about->Release();
    delete about;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1KeyPress(TObject* Sender, char& Key)
{
    if (Key == 13)//回车
    {
        make_project();
    }
}
//---------------------------------------------------------------------------
void TForm1::make_project()
{
    AnsiString str;
    str = Edit1->Text;
    std::string name = str.c_str();
    str = Edit2->Text;
    std::string path = str.c_str();

    if (strlen(name.c_str()) == 0)
    {
        Memo1->Text = "请输入组件名称！";
        return ;
    }
    if (strlen(path.c_str()) == 0)
    {
        Memo1->Text = "请输入组件存入路径！";
        return ;
    }

    WIN32_FIND_DATAA stData;
    std::string path1 = path.c_str();
    path1 += "*.*";
    HANDLE hFind = FindFirstFileA(path1.c_str(), &stData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::string str = "找不到路径:";
        str += path;
        MessageBoxA(Handle, str.c_str(), "error!", MB_OK);
        return ;
    }

	I_Tool* tool = NEW(Tool);

	ProjectType type = (ProjectType)ComboBox1->ItemIndex;//注意排列要跟枚举保持一致
	bool b = tool->MakeProject((char*)name.c_str(), (char*)path.c_str(), type,
		CheckBox1->Checked, CheckBox2->Checked);

    DEL(tool);

    if (b)
    {
        //把目录写入记录文件
        std::string currpath = Plug::GetCurrentPath();
        currpath += "sys\\Dir.ini";
        FILE* file = fopen(currpath.c_str(), "w");
        if (file)
        {
            fwrite(path.c_str(), 1, strlen(path.c_str()) + 1, file);
            fclose(file);
        }
        MessageBoxW(Handle, L"代码生成成功！", L"succeed!", MB_OK | MB_ICONINFORMATION);
	}

}

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	I_Tool* tool = NEW(Tool);
	if(tool->setupVCpath())
	{
		Memo1->Text = "配置vc路径成功！";
	}
	else
	{
        Memo1->Text = "配置vc路径出错！";
	}
}
//---------------------------------------------------------------------------


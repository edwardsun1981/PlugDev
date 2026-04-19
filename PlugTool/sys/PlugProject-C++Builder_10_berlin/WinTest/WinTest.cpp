
// WinTest.cpp: 定义应用程序的类行为。
//
#include "stdafx.h"
#include "WinTest.h"

BEGIN_MESSAGE_MAP(CWinTestApp, CWinApp)
	//ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CWinTestApp 构造
#include "../I_PlugProject.h"

CWinTestApp::CWinTestApp()
{
	INIT_PLUG
	auto gs = NEWSP(PlugProject);
	HICON icon = ::LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MAINFRAME));//GetModuleHandle(0), IDI_APPLICATION IDR_MAINFRAME
	//gs->start(icon);

	Plug::TerminateProc();
}

// 唯一的 CWinTestApp 对象
CWinTestApp theApp;

//以下这行支持windows漂亮风格必备
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "../I_ToolMui.h"
#include "resource.h"

INIT_PLUG

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	HICON icon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));//IDI_APPLICATION
	auto i = NEWSP(ToolMui);
	i->test(icon);
	//DEL(i);
	return 0;
}

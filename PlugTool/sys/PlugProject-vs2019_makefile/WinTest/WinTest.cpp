#include "../I_PlugProject.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	INIT_PLUG
	auto i = NEWSP(PlugProject);
	HICON icon = LoadIcon(hInstance, MAKEINTRESOURCE(107));//IDI_APPLICATION
	i->test();
	return 0;
}
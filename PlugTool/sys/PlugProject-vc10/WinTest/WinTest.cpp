#include "../I_PlugProject.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	INIT_PLUG
	std::shared_ptr<I_PlugProject> i = NEWSP(PlugProject);
	HICON icon = LoadIcon(hInstance, IDI_APPLICATION);
	i->test();
	return 0;
}
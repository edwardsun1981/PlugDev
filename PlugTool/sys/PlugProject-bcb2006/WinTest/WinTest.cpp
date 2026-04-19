#include "I_PlugProject.H"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	INIT_PLUG
	PlugPtr<I_PlugProject> i;
	NEWPTR(PlugProject, &i);
	HICON icon = LoadIcon(hInstance, IDI_APPLICATION);
	i->test();
	return 0;
}
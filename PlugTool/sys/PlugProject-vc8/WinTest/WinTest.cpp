#include "../I_PlugProject.H"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	INIT_PLUG
	boost::shared_ptr<I_PlugProject> i = NEWSP(PlugProject);
	HICON icon = LoadIcon(hInstance, IDI_APPLICATION);
	i->test();
	return 0;
}
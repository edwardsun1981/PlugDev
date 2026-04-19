// Test.cpp : 定义控制台应用程序的入口点。
//
#include "../I_PlugProject.H"

int main(int argc, char* argv[])
{
	std::string str = argv[0];
	str = str.substr(0, str.rfind("\\") +1);

	wchar_t path[512] = {0};
	Plug::mbstowcs(path, str.c_str(), str.size());

	Plug::SetCurrentPath(path);
	
	INIT_PLUG

	I_PlugProject* i = NEW(PlugProject);
	i->test();
	DEL(i);

	boost::shared_ptr<I_PlugProject> sp = NEWSP(PlugProject);

	return 0;
}


// Test.cpp : 定义控制台应用程序的入口点。
//
#include "../I_PlugProject.H"

int main(int argc, char* argv[])
{
	INIT_PLUG
	boost::shared_ptr<I_PlugProject> i = NEWSP(PlugProject);
	i->test();
	return 0;
}


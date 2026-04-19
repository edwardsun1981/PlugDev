// Test.cpp : 定义控制台应用程序的入口点。
//
#include "PlugProject\I_PlugProject.H"

int main(int argc, char* argv[])
{
	INIT_PLUG
	PlugPtr<I_PlugProject> i;
	NEWPTR(PlugProject, &i);
	i->test();
	return 0;
}


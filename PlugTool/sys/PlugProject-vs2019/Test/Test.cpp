// Test.cpp : 定义控制台应用程序的入口点。
//
#include "../I_PlugProject.h"

int main(int argc, char* argv[])
{
	
	INIT_PLUG

	I_PlugProject* i = NEW(PlugProject);
	i->test();
	DEL(i);
	
	//智能指针方式
	//std::shared_ptr<I_PlugProject> sp = NEWSP(PlugProject);

	return 0;
}


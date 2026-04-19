// Test.cpp : 定义控制台应用程序的入口点。
//
#include "..\I_ToolMui.H"

INIT_PLUG //一要要有这个
int main(int argc, char* argv[])
{
    I_ToolMui* i = NEW(ToolMui);
    i->test(NULL);
    i->Release();
    return 0;
}


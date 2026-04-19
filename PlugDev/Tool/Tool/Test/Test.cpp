// Test.cpp : 定义控制台应用程序的入口点。
//
#include "Tool\I_Tool.H"

int main(int argc, char* argv[])
{
    INIT_PLUG
    PlugPtr<I_Tool> i;
    NEWPTR(Tool, &i);
    i->test();
    return 0;
}


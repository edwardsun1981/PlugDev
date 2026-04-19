#include <cstdio>
#include "../I_PlugProject.h"

int main()
{
    INIT_PLUG

	auto i = NEWSP(PlugProject);
	i->test();

    printf(u8" 你好，世界， hello world!\n");
    return 0;
}


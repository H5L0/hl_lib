#include <hl.kernel.memory.h>
#include <hl.linux.syscall.h>
#include <hl.io.console.h>


int hl_init()
{
	hl_memory_init();

//#if HL_LIB_INIT_CONSOLE
	hlcsInit();
//#endif

	return 0;
}


int hl_clean()
{
	hlcsRelease();

	return 0;
}


void hl_exit(int exit_code)
{
	sys_exit((char)exit_code);
}


//The user start point.
int hlStart(void);

void _start()
//int main()
{
	hl_init();

	int exit_code = hlStart();

	hl_clean();

	hl_exit(exit_code);
}


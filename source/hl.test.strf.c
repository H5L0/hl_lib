#include <hl.io.console.h>



int hlStart()
{
	
	hlcsWriteA("----------\n", NULL);

	hlcsWriteA("[{0}] Print \"{:?______}\".\n", "i,ui", 12, 1234);

	int ch = hlcsReadChar();

	hlcsWriteA("Input char is {0}\n","i", ch);

	hlcsWriteA("----------\n", NULL);

	return 0;
}




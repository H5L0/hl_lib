#include <hl.io.console.h>
#include <hl.io.standard.h>


int hlStart()
{

	hlcsWriteA("----------\n");

	//void *args[] = {12, 1234};
	//hlcsWriteA("[{0}] Print \"{:?=___--}\".\n", "i,ui", args);

	//int ch = hlcsReadChar();

	//hlcsWriteA("Input char is {0}\n","i", ch);


	hlcsWriteA("(String,Integer) [{s:|_____________}] x=[{ui:__--}]\n", "String Test", 12, 123);

	hlcsWriteLineA("(Pointer) [{p:0x--------}]", "Pointer");

	hlcsWriteA("(中文测试) [{s:注释_______}]\n", "是中文");

	//hlcsWriteA("(Float) [{f:--.--___}]\n", 123.456f);

	hlcsWriteA("--Input------\n");

	/*
	char buffer[8];
	hlcsReadA(buffer, 8);

	hlcsWriteLineA(buffer);

	hlcsReadLineA(buffer, 8);

	hlcsWriteLineA(buffer);
	*/

	//hltwSetPointer(hl_std_output, 16, es_seek_Start);

	hlcsWriteA("\033[%1A");

	hlcsWriteLineA("*Insert*");

	hlcsWriteLineA("----------");
	return 0;
}




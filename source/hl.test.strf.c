#include <hl.io.console.h>



int hlStart()
{

	hlcsWriteA("----------\n", NULL, NULL);

	//void *args[] = {12, 1234};
	//hlcsWriteA("[{0}] Print \"{:?=___--}\".\n", "i,ui", args);

	//int ch = hlcsReadChar();

	//hlcsWriteA("Input char is {0}\n","i", ch);


	hlcsWriteA("(String,Integer) [{s:|_____________}] x=[{ui:__--}]\n", "String Test", 12, 123);

	hlcsWriteA("(Pointer) [{p:0x--------}]\n", "Pointer");

	hlcsWriteA("(中文测试) [{s:注释_______}]\n", "是中文");

	hlcsWriteA("(Float) [{f:--.--___}]\n", 123.456f);

	hlcsWriteA("----------\n", NULL, NULL);

	return 0;
}




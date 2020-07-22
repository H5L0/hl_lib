#include <hl.io.file.h>
#include <hl.io.filestream.h>
#include <hl.io.console.h>
#include <hl.chars.format.h>


int hlStart()
{
	hlPath *path = hlCreatePath("./file.txt");
	hlFile *file = hlfOpen(path, e_fa_RW);
	hlcsWriteA("Open File<0x{p}>: {i}\n", file, file->id);

	//hlfGetLatestInfo(file);
	//return 0;

	hlFileWriter *fw = hlfwCreate(file);

	/*
	const int count = 16;
	char buffer[count];
	const char *format = "---.";

	for (int i = 0; i< 20; i++)
	{
		int c = hlcf_u32(buffer, buffer + count, format, format + sizeof(format), i);
		hlfwWrite(fw, buffer, c);
	}
	*/

	hlfwWrite(fw, "Hello World!", 13);
	hlfwWrite(fw, "\n\r", 2);

	hlfwFlush(fw);
	hlfwRelease(fw);

	Bool result = hlfClose(file);
	hlcsWriteA("Close File:{ul:-}\n", result);

	return 0;
}



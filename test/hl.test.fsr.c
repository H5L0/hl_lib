#include <hl.io.file.h>
#include <hl.io.filestream.h>
#include <hl.io.console.h>
#include <hl.chars.format.h>


int hlStart()
{
	hlPath *path = hlCreatePath("./Makefile");
	hlFile *file = hlfOpen(path, e_fa_RW);  //ef_access_RW
	hlcsWriteA("Open File<0x{p}>: {i}\n", file, file->id);

	hlFileReader *fr = hlfrCreate(file);

	
	const int count = 16;
	char buffer[count];

	for (int i = 0; i< 20; i++)
	{
		//hlFileStream_Read()
		//hlfrsRead()
		//hlfwsWrite()
		//hlfsrRead()
		//hlfswWrite()
		int rcount = hlfrRead(fr, buffer, count);
		buffer[rcount == count ? count - 1 : rcount] = '\0';
		hlcsWriteA("{i} ------------------\n{s}\n", i, buffer);
	}

	Bool release_result = hlfrRelease(fr);
	hlcsWriteA("Release FileReder: {ul}\n", release_result);


	Bool result = hlfClose(file);
	hlcsWriteA("Close File: {ul}\n", result);

	return 0;
}

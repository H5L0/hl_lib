
#include <hl.io.file.h>
#include <hl.io.filestream.h>
#include <hl.kernel.io.h>

//#include <stdio.h>



int hlStart()
{
	hlPath *path = hlCreatePath("./Makefile");
	hlFile *file = hlfOpen(path, e_fa_Read);
	//printf("Create File(%p): %d\n", file, file->id);

	hlFileStream *fs = hlfsCreate(file);

	const int count = 128;
	char buffer[count];

	for (int i = 0; i< 20; i++)
	{
		int rn = hlfsRead(fs, buffer, count);
		buffer[rn - 1] = '\0';
		//printf("Read %d/%d\n", rn, count);
		//printf("\"%s\"\n", buffer);
		hl_file_write(0, "TTT\n", 4);
	}

	Bool result = hlfClose(file);
	//printf("Close File: %lu\n", result);

	return 0;
}


#include <hl.io.file.h>
#include <hl.io.filestream.h>
#include <hl.kernel.io.h>

//#include <stdio.h>



int hlStart()
{
	hlPath *path = hlCreatePath("./file.txt");
	hlFile *file = hlfOpen(path, e_fa_Read);
	//printf("Create File(%p): %d\n", file, file->id);

	//hlfGetLatestInfo(file);

	return 0;

	hlFileStream *fs = hlfsCreate(file);

	const int count = 16;
	char buffer[count];

	for (int i = 0; i< 20; i++)
	{
		int rn = hlfsRead(fs, buffer, count);
		if(rn == 0) rn = 1;
		buffer[rn - 1] = '\0';
		hl_file_write(0, buffer, rn);
	}

	Bool result = hlfClose(file);
	//printf("Close File: %lu\n", result);

	return result;
}

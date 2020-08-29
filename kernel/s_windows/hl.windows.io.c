
#include <hl.kernel.io.h>
#include <Windows.h>



int hl_file_open(const char *path, enum hlkFileAccessFlag access, enum hlkFileCreateFlag flags)
{
	OpenFile();
}

int hl_file_close(int fd)
{
	CloseFile();
}




struct hl_windows_file_stat
{
	int value1;
	int value2;
	int value3;
}



int hl_file_get_info(int fd, struct hl_stat *finfo)
{
	struct hl_windows_file_stat wfstat;
	GetFileInfo(wfstat);
	finfo->gid = 0;

	return sys_fstat(fd, finfo);
}



int hl_file_write(int fd, const void *data, int size)
{
	WriteFile();
}

int hl_file_read(int fd, void *buffer, int size)
{
	ReadFile();
}



sreg hl_file_seek(int fd, sreg offset, int mode)
{
	return sys_seek(fd, offset, mode);
}
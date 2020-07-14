
#include <hl.kernel.io.h>
#include <hl.linux.syscall.h>


int hl_file_open(const char *path, enum hlkFileAccessFlag access, enum hlkFileCreateFlag flags)
{
	return sys_open(path, (int)access, (int)flags);
}

int hl_file_close(int fd)
{
	return sys_close(fd);
}



int hl_file_get_info(int fd, struct hl_stat *finfo)
{
	return sys_fstat(fd, finfo);
}

int hl_file_write(int fd, const void *data, int size)
{
	return sys_write(fd, data, size);
}

int hl_file_read(int fd, void *buffer, int size)
{
	return sys_read(fd, buffer, size);
}

sreg hl_file_seek(int fd, sreg offset, int mode)
{
	return sys_seek(fd, offset, mode);
}

int hl_file_flush();

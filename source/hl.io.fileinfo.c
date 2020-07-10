#include <hl.string.h>
#include <hl.io.fileinfo.h>
#include <hl.system.memory.h>
//#include <hl.linux.syscall.h>


struct hlFileInfo *hlfGetLatestInfo(hlFile *file)
{
	if (file->info == NULL)
	{
		file->info = hlmeNewType(struct hlFileInfo);
	}

	return NULL;
}

struct hlFileInfo *hlfGetInfo(hlFile *file)
{
	if (file->info == NULL)
		return hlfGetLatestInfo(file);
	else
		return file->info;
}

const hlPath *hlfGetPath(hlFile *file)
{
	return file->path;
}

t_size hlfGetSize(hlFile *file)
{
	return file->info->size;
}

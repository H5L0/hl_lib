#include <hl.io.fileinfo.h>
//#include <hl.string.h>
#include <hl.kernel.io.h>
#include <hl.memory.h>

//#include <stdio.h>



u64 _hl_ftime_to_u64(struct hl_ftime *ftime)
{
	u64 t = (u64)ftime->seconds * 1000000000 + ftime->nanoseconds;
	return t;
}


struct hlFileInfo *hlfGetLatestInfo(hlFile *file)
{
	struct hl_stat stat;
	int rs = hl_file_get_info(file->id, &stat);
	if(rs == -1) return NULL;

	struct hlFileInfo *info = file->info;
	if (info == NULL)
	{
		info = hlmeNewType(struct hlFileInfo);
		return_null_if_null(info);
		file->info = info;
	}

	info->mode = stat.mode;
	info->disk = stat.rdev;
	info->uid = stat.uid;
	info->gid = stat.gid;
	info->block_size = stat.block_size;
	info->size = stat.size;
	info->time_create = _hl_ftime_to_u64(&stat.ctime);
	info->time_modify = _hl_ftime_to_u64(&stat.mtime);
	info->time_access = _hl_ftime_to_u64(&stat.atime);
	return info;
}


struct hlFileInfo *hlfGetInfo(struct hlFile *file)
{
	if (file->info == NULL)
		return hlfGetLatestInfo(file);
	else
		return file->info;
}


const hlPath *hlfGetPath(struct hlFile *file)
{
	return file->path;
}


t_size hlfGetSize(struct hlFile *file)
{
	struct hlFileInfo *info = hlfGetLatestInfo(file);
	//return_null_if_null(info);
	if(info == 0) return 0;
	return info->size;
}

u32 hlfGetBlockSize(struct hlFile *file)
{
	struct hlFileInfo *info = hlfGetInfo(file);
	if (info == NULL)
		return 0;
	else
		return info->block_size;
}


bool hlfCompareModifyTime(struct hlFile *file_new, struct hlFile *file_old)
{
	//如果文件出了问题应该提前检测, 而不是现在.
	//struct hlFileInfo *info1 = hlfGetLatestInfo(file_new);
	//if(info1 == NULL) return FALSE;
	//struct hlFileInfo *info2 = hlfGetLatestInfo(file_old);
	//if(info2 == NULL) return FALSE;

	u64 t1 = hlfGetLatestInfo(file_new)->time_modify;
	u64 t2 = hlfGetLatestInfo(file_old)->time_modify;
	return t1 < t2;
}

#pragma once
#include <hl.type.h>
#include <hl.file.structure.h>


struct hlFileInfo
{
	u16 mode;
	u16 disk;    //disk number
	u16 uid;     //id_user
	u16 gid;     //id_group
	u32 block_size;   //file store block size.
	u64 size;         //file size in byte.
	u64 time_create;  //time since 1970 in nanoseconds. (to 2554Y)
	u64 time_modify;
	u64 time_access;
};


struct hlFileInfo *hlfGetLatestInfo(struct hlFile *file);

struct hlFileInfo *hlfGetInfo(struct hlFile *file);

const struct hlPath *hlfGetPath(struct hlFile *file);

t_size hlfGetSize(struct hlFile *file);

hlFileID *_hlfGetID(struct hlFile *file);


u32 hlfGetBlockSize(struct hlFile *file);

//Is the modification time of file_new newer that file_old ?
bool hlfCompareModifyTime(struct hlFile *file_new, struct hlFile *file_old);


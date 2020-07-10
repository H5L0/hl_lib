#pragma once
#include <hl.type.h>
#include <hl.io.path.h>

//typedef t_size hlFileSize;

struct hlFileInfo
{
	u16 mode;
	u16 disk;
	u16 x1;
	u16 x2;
	t_size size;
	ureg time_create;
	ureg time_modify;
	ureg time_access;
};

typedef u32 hlFileID;

struct hlFile
{
	hlFileID id;
	const struct hlPath *path;
	struct hlFileInfo *info;
};

typedef struct hlFile hlFile;

struct hlFileInfo *hlfGetLatestInfo(struct hlFile *file);

struct hlFileInfo *hlfGetInfo(struct hlFile *file);

const struct hlPath *hlfGetPath(struct hlFile *file);

t_size hlfGetSize(struct hlFile *file);

hlFileID *_hlfGetID(struct hlFile *file);




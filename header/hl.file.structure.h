#pragma
#include <hl.type.h>
#include <hl.file.path.h>


typedef u32 hlFileID;

struct hlFile
{
	hlFileID id;
	const struct hlPath *path;
	struct hlFileInfo *info;
};





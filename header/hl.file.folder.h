#pragma once
//#include <hl.type.h>
#include <hl.file.path.h>



struct hlFolder
{
	const hlPath *path;

	//char **nodes;
	//int depth;

	struct hlFolder **sub_folders;
	int sub_count;
};


struct Folder *hlfdNew();

Bool hlfdFree(struct Folder *folder);


//hlGetFolderPath();
const struct Path *hlfdGetPath(const struct hlFolder *folder);

//获取此文件夹名
char *hlfdGetFolderName();

//获取目录名称
char *hlfdGetLayerName(const struct hlFolder *folder, int rindex);


//------------------  File System: Folder Operation ------------------//

//hlOpenFolder();
//**如果路径不存在, 应该打开失败
struct Folder *hlfdOpen(const char *path);
//hlGetFolderFromPath();
struct Folder *hlfdOpenFromPath(const struct hlPath *path);


struct Folder *hlfdCreate(const struct hlPath *path);

struct Folder *hlfdCreateSub(const struct hlPath *path, const char *name);

//error in hlGetLastError()
Bool hlfdDelete(struct hlFolder *folder);

Bool hlfdRename(struct hlFolder *folder, const char *name);

Bool hlfdMove(struct hlFolder *folder, const struct hlPath *target_path);

Bool hlfdCopy(const struct hlFolder *folder, const struct hlPath *target_path);


struct hlFile *hlfdEnumurateFile(const struct hlFolder *folder);

struct hlFolder *hlfdEnumurateFolder(const struct hlFolder *folder);



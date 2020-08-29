#pragma once
#include <hl.type.h>

//hl.fs.path.h              //name/extension/
//hl.fs.path.operation.h

//hl.fs.file.h
//hl.fs.file.access.h
//hl.fs.file.information.h
//hl.fs.file.operation.h

//hl.fs.folder.h            //name/layer
//hl.fs.folder.operation.h

//hl.fs.management.h        //file/folder: create/delete/move/rename




typedef struct hlPath hlPath;

struct hlPath
{
	const char *str;
	const char **hierarchy;
	u16 length;
	u8 count;
	bool _isFile : 1;
	bool _isLocal : 1;
};


struct hlFilePath
{
	struct hlPath;
};

struct hlFolderPath
{
	struct hlPath;
};

/*
struct hlPath *hlCreateNullPath();

//path==null: str = null, isFile = false;
//path!=null: str = copy(path), isFile = (path is file?);
struct hlPath *hlCreatePath(const char *path);

struct hlPath *hlSetPath(struct hlPath *path, const char *path_str);

//char *hlGetPathFileName(const struct hlPath* path);
//char *hlGetPathFullFileName(const struct hlPath *path);
//char *hlGetPathExtension(const struct hlPath *path);

//struct hlPath *hlGetPathFolder(const struct hlPath *path);
*/

struct hlPath *hlfpNew();
struct hlPath *hlfpCreate(const char *path);
struct hlPath *hlfpClone(const hlPath *path);
Bool hlfpFree(struct hlPath *path);

Bool hlfpDecode();

Bool hlfpSet(struct hlPath *path, const char *path_str);
Bool hlfpAdd(const struct hlPath* path, const char *sub_path);
Bool hlfpReturn(const struct hlPath *path, int step);

char *hlfpGetName(const struct hlPath* path);
char *hlfpGetFullName(const struct hlPath *path);
char *hlfpGetExtensionName(const struct hlPath *path);

int hlfpGetHierarchyCount(const struct hlPath *path);
char *hlfpGetNode(const struct hlPath *path, int depth);


//------------------  File System: Path Operation ------------------//

//路径是否存在 文件/文件夹
Bool hlfpExists(struct hlPath *path);

Bool hlfpIsFile(struct hlPath *path);

Bool hlfpIsFolder(struct hlPath *path);

Bool hlfpIsLocal(struct hlPath *path);


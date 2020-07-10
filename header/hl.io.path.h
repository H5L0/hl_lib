#pragma once
#include <hl.type.h>

typedef struct hlPath hlPath;

struct hlPath
{
    char *str;
    u16 count;
    u8 layer;
    bool isFile : 1;
    bool isLocal : 1;
};

//path==null: str = null, isFile = false;
//path!=null: str = copy(path), isFile = (path is file?);
struct hlPath *hlCreatePath(const char *path);
struct hlPath *hlSetPath(struct hlPath *path, const char *path_str);

//路径是否存在 文件/文件夹
Bool hlIsPathExists(struct hlPath *path);

//文件是否存在
Bool hlIsFileExists(struct hlPath *file);

//文件夹是否存在
Bool hlIsFolderExists(struct hlPath *folder);


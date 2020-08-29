#pragma once
#include <hl.file.folder.h>


struct Folder *hlCreateFolder(const struct hlPath *path);

struct Folder *hlCreateSubFolder(const struct hlPath *path, const char *name);

Bool hlMoveFolder(struct Folder *folder, const struct hlPath *target);

Bool 


//好像也没有必要创建一个folder来操作

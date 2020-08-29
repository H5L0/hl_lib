//hl.file.system.h
#pragma once
#include <hl.file.structure.h>
#include <hl.file.path.h>

/*

//路径是否存在 文件/文件夹
Bool hlfmPathExists(struct hlPath *file);  //hlfpExists

//文件是否存在
Bool hlfmFileExists(struct hlPath *file);  //hlfExits

//文件夹是否存在
Bool hlfmFolderExists(struct hlPath *folder);



//------------------  File System / File Management  -------------------//

//hlfsMove
Bool hlfmMove(const struct hlPath *source, const struct hlPath *target);

Bool hlfmCopy(const struct hlPath *source, const struct hlPath *target);

//删除文件/文件夹
Bool hlfmDelete(struct hlPath *path);


//遍历获取下一个子文件/文件夹
struct hlPath *hlfmEnumurateChildren();

//遍历获取下一个子文件
struct hlPath *hlfmEnumurateSubFiles();

//遍历获取下一个子文件夹
struct hlPath *hlfmEnumurateSubFolders();


struct hlPath *hlfmGetNextSubObject(const struct hlPath *folder, int *count);
struct hlPath *hlfmGetNextSubFile();
struct hlPath *hlfmGetNextSubFolder();


void *hlfmGetSubFiles(struct hlPath *folder, const char *rule, int resursive, int amount_max);

void *hlfmGetSubFolders(struct hlPath *folder, int amount_max);

void *hlfmGetSubPaths(struct hlPath *folder, int amount_max);

*/

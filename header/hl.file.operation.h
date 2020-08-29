#pragma once
#include <hl.file.structure.h>


//-------------------------- File Structure-------------------------//
//hl.file.structure.h ?

//hlFileAccessFlag
enum hlFileAccess
{
	ef_Read  = 0b001,   //eFileAccess_Read
	ef_Write = 0b010,
	ef_ReadAndWrite = 0b011,

	ef_R = ef_Read,   //eFileAccess_Read
	ef_W = ef_Write,
	ef_RW = ef_ReadAndWrite
};

//hlFilePermissionMode
enum hlFilePermission
{
	ef_pm_User = 0,
	ef_pm_UserGroup = 1,
	ef_pm_Other = 2,
};

//hlFileSecurityType
enum hlFileSecurity
{
	ef_se_User  = 0,
	ef_se_Group = 1,
	ef_se_Other = 2,
};


//------------------  File System: File Operation ------------------//

struct hlFile *hlfOpen(const struct hlPath *path, enum hlFileAccess access);
struct hlFile *hlfOpenEx(const struct hlPath *path, enum hlFileAccess access, int share_type); //r/w

struct hlFile *hlfCreate(const struct hlPath *path);
struct hlFile *hlfCreateEx(const struct hlPath *path, int share_type, enum hlFilePermission permission);

struct hlFile *hlfOpenOrCreate(const struct hlPath *path);
struct hlFile *hlfOpenOrCreateEx(const struct hlPath *path, enum hlFilePermission permission);


Bool hlfClose(struct hlFile *file);


//rename and create a new file structure.
//delete original file.
struct hlFile *hlfRename(const struct hlFile *file);

struct hlFile *hlfMove(const struct hlFile *file, const struct hlPath *target);

struct hlFile *hlfCopy(const struct hlFile *file, const struct hlPath *target);

//删除文件
//返回值[Bool]: 删除是否成功
Bool hlfDelete(struct hlFile *file);


//Bool hlfExists(struct hlFilePath *file);

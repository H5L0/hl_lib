#pragma once
#include <hl.type.h>
//#include <hl.macro.bit.h>
#include <hl.io.path.h>
#include <hl.io.fileinfo.h>

//hl.fs.path.h
//hl.fs.file.h     <-只定义结构和枚举
//hl.fs.folder.h
//hl.fs.file.io.h
//hl.fs.manager.h  <-可以操作文件: 创建/删除/移动/复制/重命名/链接

//hl.file.system.h
//hl.file.manager
//hl.file.io.h    x
//hl.file.path.h  x
//hl.file.folder.h

//    path
//(file...info...date...time...)
// file  folder
//  manager


//-------------------------- File Structure-------------------------//

enum hlFileAccess
{
	ef_Read  = 0b001,   //eFileAccess_Read
	ef_Write = 0b010,
	ef_RW    = 0b011,
};

enum hlFilePermission
{
	ef_pm_User = 0,
	ef_pm_UserGroup = 1,
	ef_pm_Other = 2,
};

enum hlFileSecurity
{
	//e_io_User,
	//e_io_Group,
	//e_io_Other,

	ef_sec_User  = 0,
	ef_sec_Group = 1,
	ef_sec_Other = 2,
};

//--------------------- File System ----------------------//

struct hlFile *hlfOpen(const struct hlPath *path, enum hlFileAccess access);
struct hlFile *hlfOpenEx(const struct hlPath *path, enum hlFileAccess access, int share_type); //r/w

struct hlFile *hlfCreate(const struct hlPath *path);
struct hlFile *hlfCreateEx(const struct hlPath *path, int share_type, enum hlFilePermission permission);

struct hlFile *hlfOpenOrCreate(const struct hlPath *path);
struct hlFile *hlfOpenOrCreateEx(const struct hlPath *path, enum hlFilePermission permission);

Bool hlfClose(struct hlFile *file);

//删除文件/文件夹
//返回值[Bool]: 删除是否成功
Bool hlfDelete(struct hlPath *path);

//Bool hlfsDeleteFile(hlPath *file);
//Bool hlfsDeleteFolder(hlPath *file);

//--------------------- File IO ----------------------//

//...block/count
int hlfRead(struct hlFile *file, void *buffer, int length);

int hlfWrite(struct hlFile *file, const void *data, int length);

enum hlFileSeekMode
{
	ef_seek_Start  = 0,  //eFileSeekMode_Start
	ef_seek_Offset = 1,
	ef_seek_End    = 2,
	ef_seek_Data = -1,
	ef_seek_Hole = -1,

	//efSeekStart
};

//失败返回-1
t_offset hlfSeek(struct hlFile *file, t_offset offset, enum hlFileSeekMode mode);

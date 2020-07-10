#pragma once
#include <hl.type.h>
#include <hl.macro.bit.h>
#include <hl.io.path.h>
#include <hl.io.fileinfo.h>

//-------------------------- File Structure-------------------------//

enum hlFileAccess
{
    e_fa_Read  = 0b001,
    e_fa_Write = 0b010,
    e_fa_RW    = 0b011,
};

enum hlFilePermission
{
    e_fp_User = 0,
    e_fp_UserGroup = 1,
    e_fp_Other = 2,
};

enum hlFileSecurity
{
    e_io_User,
    e_io_Group,
    e_io_Other,
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

int hlfWrite(struct hlFile *file, void *data, int length);

enum hlFileSeekMode
{
    e_fseek_start = 0,
    e_fseek_offset = 1,
    e_fseek_end = 2,
    e_fseek_data,
    e_fseek_hole,
};

//失败返回-1
t_offset hlfSeek(struct hlFile *file, t_offset offset, enum hlFileSeekMode mode);

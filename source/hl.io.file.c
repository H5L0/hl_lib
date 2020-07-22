#include <hl.io.file.h>
#include <hl.kernel.io.h>
#include <hl.system.memory.h>
#include <hl.string.h>



struct hlFile *_hlCreateFile(int fd, const struct hlPath *path, struct hlFileInfo *info)
{
    struct hlFile *file = hlmeNewType(struct hlFile);
    file->id = fd;
    file->path = path;
    file->info = NULL;
    return file;
}


struct hlFile *hlfOpen(const struct hlPath *path, enum hlFileAccess permission)
{
    return hlfOpenEx(path, permission, 0);
}

struct hlFile *hlfOpenEx(const struct hlPath *path, enum hlFileAccess permission, int share_type)
{
    int access = (int)permission - 1;
    //create mode is only valid while creating file.
    int cmode = 0;

    int fd = hl_file_open(path->str, access, cmode);
    //why sometimes fd is -2?
    if(fd < 0) return NULL; 

    return _hlCreateFile(fd, path, NULL);
}


struct hlFile *hlfCreate(const struct hlPath *path)
{
    return hlfCreateEx(path, 0, 0);
}

struct hlFile *hlfCreateEx(const struct hlPath *path, int share_type, enum hlFilePermission permission)
{
    int access = ek_faT_ReadWrite;
    int mode = ek_fcF_Default;

    int fd = hl_file_open(path->str, access, mode);
    if (fd == -1) return NULL;

    return _hlCreateFile(fd, path, NULL);
}


Bool hlfClose(struct hlFile *file)
{
    //返回-1为FALSE, 0为TRUE.
    return !hl_file_close(file->id);
}



int hlfRead(struct hlFile *file, void *buffer, int length)
{
    return hl_file_read(file->id, buffer, length);
}

int hlfWrite(struct hlFile *file, const void *data, int length)
{
    return hl_file_write(file->id, data, length);
}

t_offset hlfSeek(struct hlFile *file, t_offset offset, enum hlFileSeekMode mode)
{
    return hl_file_seek(file->id, offset, mode);
}

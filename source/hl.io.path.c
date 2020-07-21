
#include <hl.io.path.h>
#include <hl.system.memory.h>
#include <hl.chars.h>



struct hlPath *hlCreatePath(const char *path)
{
    struct hlPath *hlp = hlmeNewType(struct hlPath);
    u16 length = hl_chars_length(path);
    hlp->str = hlmeNewCopy(path, length + 1);
    hlp->count = length;
    hlp->layer = 0;
    hlp->isFile = FALSE;
    hlp->isLocal = FALSE;
    return hlp;
}

struct hlPath *hlSetPath(struct hlPath *path, const char *path_str)
{
    return NULL;
}
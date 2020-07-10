#include <hl.type.h>

//文件操作错误码
//static u32 __hlfs_error;

//库操作失败后的错误码
u32 hlGetErrorCode();

//库操作失败后的错误消息
const char *hlGetError();


/*
EEXIST 参数 pathname 所指的文件已存在,却使用了 O_CREAT和 O_EXCL 旗标

　　EACCESS 参数 pathname 所指的文件不符合所要求测试的权限。

　　EROFS 欲测试写入权限的文件存在于只读文件系统内。

　　EFAULT 参数 pathname 指针超出可存取内存空间。

　　EINVAL 参数 mode 不正确。

　　ENAMETOOLONG 参数 pathname 太长。

　　ENOTDIR 参数 pathname 不是目录。

　　ENOMEM 核心内存不足。

　　ELOOP 参数 pathname 有过多符号连接问题。

　　EIO I/O 存取错误。
*/


#pragma once
#include <hl.type.h>

//w/x/m
//windows/linux/macos

//-----------------------  file operation  ---------------------//

//0 读取数据
//     fd: 文件号
// buffer: 读取储存缓存
//  count: 读取字节数 < 0x7FFF0000
int sys_read(int fd, void *buffer, int count);

//1 写入数据
int sys_write(int fd, const void *buffer, int count);

//2 打开文件
int sys_open(const char *path, int access, int flags);

//3 关闭文件
int sys_close(int fd);

//5 获取文件信息
int sys_fstat(int fd, void *stat);

//8 更改文件指针位置
sreg sys_seek(int fd, sreg offset, int mode);

//
int sys_fsync();

//


//-----------------------  memory management  ---------------------//

//9 内存映射/分配虚拟空间
//  start: 制定映射的地址 / NULL自动分配空闲位置
//   prot: 内存属性
//  flags: 
//     fd: 映射文件号
// offset: 映射文件的起始偏移
void *sys_mmap(void *start, ureg length, int prot, int flags, int fd, sreg offset);

//10 为虚拟空间设定属性
//     start: 起始地址 内存分页对齐 (4KB)
//    length: 长度 内存分页倍数
// attribute: READ | WRITE | EXEC | NONE
void *sys_mprotect(const void *start, ureg length, int attribute);

//11 取消分配的虚拟空间
//  start: 起始地址
// length: 长度
int sys_munmap(void *start, ureg length);

//12 设定新的堆结束地址
void *sys_brk(void *addr_end);


//---------------------  process management  ---------------------//

//56 进程克隆
//pid_t *ptid, struct user_desc *tls, pid_t *ctid
int sys_clone(int (*fstart)(void *), void *child_stack, int flags, void *arg);

//57 进程分支
int sys_fork();

//58 进程轻分支
int sys_vfork();

//59 执行新进程
int sys_exec();

//60 进程退出
void sys_exit(char exit_code);











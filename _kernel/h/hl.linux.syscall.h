#pragma once
#include <hl.type.h>

//w/x/m
//windows/linux/macos

//0 读取数据
//fd: 文件号
//buffer: 读取储存缓存
//count: 读取字节数 < 0x7FFF0000
int sys_read(int fd, void *buffer, int count);

//1 写入数据
int sys_write(int fd, const void *buffer, int count);

//2
int sys_open(const char *path, int access, int flags);

//3
int sys_close(int fd);

//8
sreg sys_seek(int fd, sreg offset, int mode);

int sys_flush();


//9 内存映射/分配虚拟空间
//start: 制定映射的地址 / NULL自动分配空闲位置
//prot: 内存属性
//flags: 
//fd: 映射文件号
//offset: 映射文件的起始偏移
void *sys_mmap(void *start, ureg length, int prot, int flags, int fd, sreg offset);

//10 为虚拟空间设定属性
//start: 起始地址 内存分页对齐 (4KB)
//length: 长度 内存分页倍数
//protect_type: READ | WRITE | EXEC | NONE
void *sys_mprotect(const void *start, ureg length, int attribute);

//11 取消分配的虚拟空间
//start: 起始地址
//length: 长度
int sys_munmap(void *start, ureg length);

//12 设定新的堆结束地址
void *sys_brk(void *addr_end);




void sys_exit(char exit_code);

int sys_exec();



int sys_fork();



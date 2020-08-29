#pragma once
#include <hl.type.h>
#include <hl.macro.bit.h>

//**改名为hl.os.io.h
//**hl.base.io.h <-> hl.linux.io.c
//**hl.core.io.h <-> hl.linux.core.io.c
//**hl.api.io.h  <-> hl.linux.api.io.c
//**hl.in.io.h   <-> hl.in.io.linux.c    <-> hl.linux.in.io.c


enum hlkFileAccessFlag
{
	ek_faT_ReadOnly  = 0,
	ek_faT_WriteOnly = 1,
	ek_faT_ReadWrite = 2,
	//hlkFileAccessFlag_Check = 3,

	ek_faF_Create         = BIT(6),
	ek_faF_EnsureCreate   = BIT(7), //必须和Create一起用
	ek_faF_NoCtrlTerminal = BIT(8),
	ek_faF_Truncate       = BIT(9),
	ek_faF_Append         = BIT(10),
	ek_faF_NonBlock       = BIT(11),
	ek_faF_Sync           = BIT(12) | BIT(20),
	ek_faF_DSync          = BIT(12),
	ek_faF_Async          = BIT(13),
	ek_faF_Direct         = BIT(14),
	ek_faF_LargeFile      = BIT(15),
	ek_faF_Directory      = BIT(16),
	ek_faF_NoFollow       = BIT(17),
	ek_faF_NoAccessTime   = BIT(18),
	ek_faF_CloExec        = BIT(19),
	ek_faF_Path           = BIT(21),
	ek_faF_TempFile       = BIT(22) | BIT(16),

	//hlFileAccessFlag_Text = 0x4000, //翻译CR-LF控制字符
	//hlFileAccessFlag_Binary = 0x8000,

	//ekf_access_(my_flag)
};

enum hlkFileCreateFlag
{
	//此用户
	ek_fcF_R = 0x0400,
	ek_fcF_W = 0x0200,
	ek_fcF_E = 0x0100,
	//用户组
	ek_fcF_R_G = 0x0040,
	ek_fcF_W_G = 0x0020,
	ek_fcF_E_G = 0x0010,
	//其他用户
	ek_fcF_R_O = 0x0004,
	ek_fcF_W_O = 0x0002,
	ek_fcF_E_O = 0x0001,

	ek_fcF_RWE = 0x0700,
	ek_fcF_RWE_G = 0x0070,
	ek_fcF_RWE_O = 0x0007,

	//文件常用标识
	ek_fcF_Default = ek_fcF_R | ek_fcF_W | ek_fcF_R_O | ek_fcF_W_O,
};



struct hl_ftime
{
	s64 seconds;
	union
	{
		//10^-9s
		u64 nanoseconds;
		struct 
		{
			u32 nanoseconds_u32;
			u32 __padding_32; //仅对小段模式有效
		};
	};
};

/*
[00] 07 08 00 00 00 00 00 00 divice      64
[01] 7d 8d 01 00 00 00 00 00 ino         64
[02] 01 00 00 00 00 00 00 00 mode |nlink 32
[03] ff 81 00 00 e8 03 00 00 uid  |gid   32
[04] e8 03 00 00 00 00 00 00 rdev?
[05] 00 00 00 00 00 00 00 00 padding?
[06] 09 00 00 00 00 00 00 00 size        64
[07] 00 10 00 00 00 00 00 00 block_size  64/32 padding
[08] 01 00 00 00 00 00 00 00 block_count 64/32 padding
[09] d1 21 0b 5f 00 00 00 00 atime       64
[10] 74 28 04 19 00 00 00 00
[11] f2 0f 0b 5f 00 00 00 00 mtime       64
[12] e0 b1 50 18 00 00 00 00
[13] f2 0f 0b 5f 00 00 00 00 ctime       64
[14] e0 b1 50 18 00 00 00 00
*/

struct hl_stat
{
	u64 device;     /* Device.  */
	u64 ino;        /* File serial number.  */
	u32 mode;       /* File mode.  */
	u32 nlink;      /* Link count.  */

	u32 uid;        /* User ID of the file's owner.  */
	u32 gid;        /* Group ID of the file's group. */

	u64 rdev;       /* Device number, if device.  */
	u64 __pad1_64;

	s64 size;       /* Size of file, in bytes.  */

	s32 block_size; /* Optimal block size for I/O.  */
	u32 __pad2_32;

	u64 block_count;/* Number 512-byte blocks allocated. */

	struct hl_ftime atime; /* Time of last access.  */
	struct hl_ftime mtime; /* Time of last modification.  */
	struct hl_ftime ctime; /* Time of last status change.  */

	u32 __unused[16];
};



//打开文件
//#目前是对linux系统调用的简单封装
int hl_file_open(const char *path, enum hlkFileAccessFlag access, enum hlkFileCreateFlag flags);

//关闭文件
//失败返回-1, 成功返回0
int hl_file_close(int fd);

//int hl_file_rename();

//hl_file_quiry();
//这个函数保证使用最新的stat函数, 结果为64位.
//失败返回-1
int hl_file_get_info(int fd, struct hl_stat *finfo);

//移动文件指针
//失败返回-1, 成功返回新位置
sreg hl_file_seek(int fd, sreg offset, int mode);

//文件写入
int hl_file_write(int fd, const void *data, int size);

//文件读取
int hl_file_read(int fd, void *buffer, int size);

//int hl_file_flush();
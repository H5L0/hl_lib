#pragma once
#include <hl.type.h>
#include <hl.macro.bit.h>

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

int hl_file_open(const char *path, enum hlkFileAccessFlag access, enum hlkFileCreateFlag flags);

//失败返回-1, 成功返回0
int hl_file_close(int fd);

//失败返回-1, 成功返回新位置
sreg hl_file_seek(int fd, sreg offset, int mode);

int hl_file_rename();

int hl_file_flush();

int hl_file_write(int fd, const void *data, int size);

int hl_file_read(int fd, void *buffer, int size);

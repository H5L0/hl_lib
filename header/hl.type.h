#pragma once


//手动定义系统的寄存器位宽
#define _XBW 64

#if _XBW == 64
#define _X64
#endif

#ifndef _X64
typedef signed long sreg;
typedef unsigned long ureg;
#define _XSHIFT 2
#else
typedef signed long long sreg;
typedef unsigned long long ureg;
#define _XSHIFT 3
#endif

#define _XLEN (1 << _XSHIFT)

typedef unsigned char bool; //单字节布尔值
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;

typedef ureg Bool; //系统字长布尔值

//改为8字节？
//typedef sreg slong; //4/8字节有符号整数
//typedef ureg ulong; //4/8字节无符号整数

//typedef signed long Int32;
//typedef unsigned long UInt32;

typedef signed char s8;         //固定1字节有符号整数
typedef unsigned char u8;       //固定1字节无符号整数
typedef signed short s16;       //固定2字节有符号整数
typedef unsigned short u16;     //固定2字节无符号整数
typedef signed int s32;         //固定4字节有符号整数
typedef unsigned int u32;       //固定4字节无符号整数
typedef signed long long s64;   //固定8字节有符号整数
typedef unsigned long long u64; //固定8字节无符号整数

typedef ureg t_size;     //内存大小类型，32/64位对应
typedef sreg t_offset;   //偏移大小类型，32/64位对应 //t_ofs

typedef void *t_pointer; //指针类型，32/64位对应
typedef void *t_ptr;

typedef ureg t_address; //指针(地址)类型，32/64位对应
typedef ureg t_addr;    //指针(地址)类型，32/64位对应

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

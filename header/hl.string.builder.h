/*
#pragma once
#include <hl.string.h>
#include <hl.system.memory.buffer.h>


typedef struct hlStringBuilder
{
	struct hlMemoryBuffer mbuffer;
	bool ;
}hlStringBuilder;


bool hlsbCreateFromSpace(void *space, int size)
{
	//hlCacheSpace_Create()
	return TRUE;
}

bool hlsbCreate(int capcity)
{
	hlMemoryBuffer_Init()
}

bool hlsbAppendChars(struct hlStringBuilder *sb, const char *chars, int length)
{
	return hlCacheSpace_Add(&sb->mbuffer, chars, length);
}

bool hlsbAppendChar(struct hlStringBuilder *sb, char ch)
{
	return hlCacheSpace_AddByte(&sb->mbuffer, (byte)ch);
}

hlStringA *hlsbToStringA(struct hlStringBuilder *sb)
{
	hlStringA *newstr = hlNew();
	return_null_if_null(newstr);
	hlsaCopyCharsInLen(newstr, sb->mbuffer.space, sb->mbuffer.count);
	return newstr;
}

bool hlsbRelease(struct hlStringBuilder *sb)
{
	
}


*/
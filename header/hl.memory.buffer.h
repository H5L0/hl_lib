#pragma once


//hlCacheSpace
//hlBufferSpace

struct hlMemoryBuffer
{
	//hlList
	void *space;
	int count;
	int capcity;
	bool realloced;
};

//...hlmbInit()
//...hlmbAdd()

bool hlMemoryBuffer_Init(struct hlMemoryBuffer *mb, void *space, int capcity);
bool hlMemoryBuffer_InitNewSpace(struct hlMemoryBuffer *mb, int capcity);

bool hlMemoryBuffer_Resize(struct hlMemoryBuffer *mb, int newCpacity);

bool hlMemoryBuffer_Add(struct hlMemoryBuffer *mb, const void *data, int size);
bool hlMemoryBuffer_AddByte(struct hlMemoryBuffer *mb, byte b);

bool hlMemoryBuffer_Release(struct hlMemoryBuffer *mb);
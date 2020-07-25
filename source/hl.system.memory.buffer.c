#include <hl.system.memory.buffer.h>
#include <hl.system.memory.h>


//...hlmbInit()
//...hlmbAdd()


bool hlMemoryBuffer_Init(struct hlMemoryBuffer *mb, void *space, int capcity)
{
	mb->space = space;
	mb->count = 0;
	mb->capcity = capcity;
	mb->realloced = FALSE;
}

bool hlMemoryBuffer_InitNewSpace(struct hlMemoryBuffer *mb, int capcity)
{
	mb->space = hlmeNew(capcity);
	return_false_if_null(mb->space);
	mb->capcity = capcity;
	mb->count = 0;
	mb->realloced = TRUE;
}

bool hlMemoryBuffer_Resize(struct hlMemoryBuffer *mb, int newCpacity)
{
	void *newSpace = hlmeNew(newCpacity);
	hlmeCopy(mb->space, newSpace, mb->capcity);
	if(mb->realloced) 
	{
		hlmeFree(mb->space);
	}
	mb->realloced = TRUE;
	return TRUE;
}


bool hlMemoryBuffer_Add(struct hlMemoryBuffer *mb, const void *data, int size)
{
	mb->count += size;
	if(mb->count + size > mb->capcity)
	{
		/********** TODO: ***********/
		if(mb->realloced)
		{
			mb->space = hlmeResize(mb->space, mb->capcity * 2);
		}
		else
		{
			void *newSpace = hlmeNew(mb->capcity * 2);
			hlmeCopy(mb->space, newSpace, mb->capcity);
		}
		mb->capcity *= 2;
	}
}

bool hlMemoryBuffer_AddByte(struct hlMemoryBuffer *mb, byte b)
{
	/************* TODO: *************/
	if(mb->count == mb->capcity)
	{

	}
	((byte*)mb->space)[mb->count] = b;
	mb->count ++;
	return TRUE;
}


bool hlMemoryBuffer_Release(struct hlMemoryBuffer *mb)
{
	if(mb->realloced)
	{
		return hlmeFree(mb->space);
	}
	else return TRUE;
}


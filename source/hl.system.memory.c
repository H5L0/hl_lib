#include <hl.system.memory.h>
#include <hl.kernel.memory.h>



void *hlmeNew(t_size size)
{
	return hl_memory_alloc(size);
}


Bool hlmeResizeOnly(void *space, t_size newSize)
{
	//仅尝试修改大小
	return hl_memory_resize(space, newSize);
}


Bool hlmeFree(void *space)
{
	return hl_memory_free(space);
}


//------------------------------------//


void *hlmeNewClear(t_size size)
{
	void *space = hlmeNew(size);
	return_null_if_null(space);
	hlmeClear(space, size);
	return space;
}

void *hlmeNewArray(t_size size_element, t_size length)
{
	return hlmeNew(size_element * length);
}

void *hlmeNewCopy(const void *source, t_size size)
{
	void *space = hlmeNew(size);
	return_null_if_null(space);
	hlmeCopyR(space, source, size);
	return space;
}




//传入NULL： 分配新空间
//传入有效空间：
//	调整大小失败：分配新空间
//	调整大小成功：返回原空间地址
void *hlmeResize(void *space, t_size newSize)
{
	if(space == NULL) return hlmeNew(newSize);
	else
	{
		if(hlmeResizeOnly(space, newSize)) return space;
		else return hlmeNew(newSize);
	}
}


//-----------------------------------------------------------------------//

void hlmeCopy(const void *source, void *destination, t_size size)
{
	t_size count_align = size >> _XBIT;
	t_size count_rm = size - (count_align << _XBIT);
	for (t_size i = 0; i < count_align; i++)
	{
		((ureg *)destination)[i] = ((ureg *)source)[i];
	}
	for (t_size i = 0; i < count_rm; i++)
	{
		((byte *)destination)[i] = ((byte *)source)[i];
	}
}

void hlmeCopyR(void *destination, const void *source, t_size size)
{
	hlmeCopy(source, destination, size);
}

void hlmeFill(void *source, char ch, t_size count)
{
	for(t_size i=0; i<count; i++)
	{
		((u8*)source)[i] = ch;
	}
}

void hlmeClear(void *source, t_size size)
{
	hlmeFill(source, 0, size);
}

Bool hlmeIsEqual(const void *source1, const void *source2, t_size size)
{
	for(t_size i=0; i<size; i++)
	{
		if(((u8*)source1 + i) != ((u8*)source2 + i)) return FALSE;
	}
	return TRUE;
}


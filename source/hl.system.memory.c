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
	hlmeCopy(source, space, size);
	return space;
}




//传入NULL： 分配新空间
//传入有效空间：
//  调整大小失败: 分配新空间
//  调整大小成功: 返回原空间地址
//  重新分配空间: 复制内容,释放原空间,返回新空间
void *hlmeResize(void *space, t_size newSize)
{
	if(space == NULL)
	{
		return hlmeNew(newSize);
	}
	else if(hlmeResizeOnly(space, newSize))
	{
		return space;
	}
	else
	{
		void *newSpace = hlmeNew(newSize);
		return_null_if_null(newSpace);

		t_size oriSize = hl_mem_get_size(space);
		hlmeCopy(space, newSpace, oriSize);

		hlmeFree(space);
		//if failed => hlmeFree(newSpace);
		return newSpace;
	}
}


//-----------------------------------------------------------------------//

void hlmeCopy(const void *source, void *destination, t_size size)
{
	void *end_align = destination + ((size >> _XSHIFT) << _XSHIFT);
	void *end_rm = destination + size;

	while (destination != end_align)
	{
		*(ureg *)destination = *(ureg *)source;
		destination += sizeof(ureg);
		source += sizeof(ureg);
	}

	while (destination != end_rm)
	{
		*(u8 *)destination = *(u8 *)source;
		++destination;
		++source;
	}
}


void hlmeFill(void *dest, char ch, t_size count)
{
	ureg com = ch;
	com = (com <<  8) | com;
	com = (com << 16) | com;
	if(sizeof(ureg) > 4)
		com = (com << 32) | com;

	t_size count_align = count >> _XSHIFT;
	void *end = ((ureg *)dest) + count_align;
	while (dest != end)
	{
		*(ureg *)(dest++) = com;
	}

	t_size count_rm = count - (count_align << _XSHIFT);
	end = ((char *)dest) + count_rm;
	while (dest != end)
	{
		*(char *)(dest++) = ch;
	}
}


void hlmeClear(void *source, t_size size)
{
	hlmeFill(source, 0, size);
}


Bool hlmeIsEqual(const void *source1, const void *source2, t_size size)
{
	for(t_size i = 0; i < size; i++)
	{
		if(((u8*)source1 + i) != ((u8*)source2 + i)) return FALSE;
	}
	return TRUE;
}


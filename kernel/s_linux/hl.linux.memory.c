#include <hl.kernel.memory.h>
#include <hl.linux.syscall.h>


struct Area
{
	struct Area *pNext;
	struct Area *pLast;
	void *end;
	char data[0];
};


#define _ALIGN_BIT 3
#define _LARGE_OBJ_SIZE (1<<15)


void *_hl_heap_start;
void *_hl_heap_end;


static inline bool _SetHeapEnd(void *end)
{
	if(sys_brk(end) != end) return FALSE;
	_hl_heap_end = end;
	return TRUE;
}



void hl_memory_init()
{
	_hl_heap_start = sys_brk(NULL);
	_hl_heap_end = _hl_heap_start;
}


void *hl_memory_alloc(t_size size)
{
	if (size == 0) return NULL;

	//4/8字节对齐
	const t_size align_mask = (1 << _ALIGN_BIT) - 1;
	size = (size + sizeof(struct Area) + align_mask) & (~align_mask);

	//初始首内存区
	struct Area *ta = (struct Area*)_hl_heap_start;
	void *t_end = (void *)ta + size;

	//目前未分配内存
	if(_hl_heap_start == _hl_heap_end)
	{
		if(!_SetHeapEnd(t_end)) return NULL;

		ta->pNext = NULL;
		ta->pLast = NULL;
		ta->end = t_end;
		return ta->data;
	}

	if(ta->end != NULL) t_end = ta->end + size;
	
	//沿着链表遍历
	//L_SearchNext:;
	while(TRUE)
	{
		if(ta->pNext == NULL)
		{
			if((void*)_hl_heap_end >= t_end) break;

			if(_SetHeapEnd(t_end)) break;
			else return NULL;
		}
		else
		{
			if((void*)ta->pNext >= t_end) break;
		}

		ta = ta->pNext;
		t_end = ta->end + size;
	}

	if(ta->end == NULL)
	{
		ta->end = t_end;
		return ta->data;
	}
	else
	{
		struct Area *newa = (struct Area *)ta->end;
		newa->pLast = ta;
		newa->pNext = ta->pNext;
		newa->end = t_end;
		ta->pNext = newa;
		return newa->data;
	}
}



bool hl_memory_resize(void *space, t_size size)
{
	//if(space == NULL) return FALSE;
	struct Area *ta = (struct Area *)((t_addr)space - sizeof(struct Area));

	//4/8字节对齐
	t_size align_mask = (1 << _ALIGN_BIT) - 1;
	size = (size + align_mask) & (~align_mask);
	void *t_end = space + size;

	//最后一个区块通常都可以扩容
	if(ta->pNext == NULL)
	{
		if(_hl_heap_end < t_end)
		{
			//堆尾扩容失败
			if(!_SetHeapEnd(t_end)) return FALSE;
		}
	}
	//中间区块扩容空间不足
	else if((void*)ta->pNext < t_end) return FALSE;

	ta->end = t_end;
	return TRUE;
}



bool hl_memory_free(void *space)
{
	if(space == NULL) return FALSE;

	struct Area *ta = (struct Area *)((t_addr)space - sizeof(struct Area));

	//首区块
	if(ta == _hl_heap_start)
	{
		//只有这一个区块, 清除整个堆
		if(ta->pNext == NULL)
		{
			return _SetHeapEnd(_hl_heap_start);
		}
		//置空首区块
		else
		{
			ta->end = NULL;
			return TRUE;
		}
	}
	//尾区块
	else if(ta->pNext == NULL)
	{
		struct Area *lasta = ta->pLast;
		//上一个是首区块, 且已经置空, 可以清除整个堆
		if(lasta->end == NULL)
		{
			return _SetHeapEnd(_hl_heap_start);
		}
		else
		{
			//如果末尾剩余空间大于32KB, 还给系统
			//t_addr align_ta; //可以不处理PageAlign
			if(_hl_heap_end >= lasta->end + _LARGE_OBJ_SIZE)
			{
				if(!_SetHeapEnd(lasta->end)) return FALSE;
			}

			lasta->pNext = NULL;
			return TRUE;
		}
	}
	else
	{
		ta->pLast->pNext = ta->pNext;
		return TRUE;
	}
}



/*

struct Area * _head_area;


void _hl_memory_init()
{
	_hl_heap_start = sys_brk(NULL);
	_hl_heap_end = _hl_heap_start;
	_head_area = NULL;
}


void *_hl_memory_alloc(t_size size)
{
	size = size + sizeof(struct Area);
	void* t_end;

	if(_head_area == NULL)
	{
		t_end = _hl_heap_start + size;
		if(!_SetHeapEnd(t_end)) return NULL;

		_head_area = (struct Area*)_hl_heap_start;
		_head_area->pLast = NULL;
		_head_area->pNext = NULL;
		_head_area->end = t_end;
		return _head_area->data;
	}
	else
	{
		struct Area *ta = _head_area;
		//沿着链表遍历
		while(TRUE)
		{
			//抵达末尾
			if(ta->pNext == NULL) goto L_AppendArea;
			//空隙空间足够
			t_end = ta->end + size;
			if((t_addr)ta->pNext > (t_addr)t_end) goto L_InsertArea;

			ta = ta->pNext;
		}

		L_AppendArea:
		//在末尾增加区块
		if((t_addr)_hl_heap_end < (t_addr)t_end)
		{
			if(!_SetHeapEnd(t_end)) return NULL;
		}

		L_InsertArea:;
		struct Area *newa = (struct Area *)ta->end;
		newa->pLast = ta;
		newa->pNext = ta->pNext;
		newa->end = t_end;
		ta->pNext = newa;
		return newa->data;
	}

}


bool _hl_memory_free(void *space)
{
	struct Area *ta = (struct Area *)((t_addr)space - sizeof(struct Area));
	
	//第一个
	if(ta->pLast == NULL)
	{
		//同时也是最后一个
		if(ta->pNext == NULL) 
		{
			if(!_SetHeapEnd(_hl_heap_start)) return FALSE;
			_head_area = NULL;
			return TRUE;
		}
		else
		{
			_head_area = ta->pNext;
			_head_area->pLast = NULL;
			return TRUE;
		}
	}
	else
	{

	}


}


*/



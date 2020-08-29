#pragma once
#include <hl.type.h>
#include <hl.macro.bit.h>

/*

void hlmeAllocateHeap();
void hlmeReleaseHeap();


typedef void *hlHeap;


void hlmeNewH(hlHeap heap, t_size);

*/


#if 0
struct hlMemoryBlockRecorder
{
	int block_size;
	int chunk_count;
	struct hlMemoryBlockRecorder *next;
	void *pointer;
	ureg usage[0];
	//...可以适当预留usage
};


int find_first_bit(ureg value);


void *find_first_space(struct hlMemoryBlockRecorder *mbr)
{
	for(int i = 0; i < mbr->chunk_count; i++)
	{
		if(mbr->usage[i] != 0)
		{
			int pos = find_first_bit(mbr->usage[i]);

			int index = i << (_XSHIFT + 3) + pos;

			void *block = mbr->pointer + index * mbr->block_size;

			SET_BIT(mbr->usage[i], pos);

			return block;
		}
	}

	return NULL;
}
#endif



//** TODO: 实现小块内存分配器 **//
#include <hl.memory.h>


//每个bit代表的空间字节大小
// 8: sizeof(void *) 一个指针的大小
//16: sizeof(void *) + sizeof(u64) 一个较小结构体的大小
#define MC_SIZE_PBIT 16


//专为小内存分配设计的内存块管理器
struct hlMemoryChunkManager
{
	int unit_size;    //每个bit代表的字节大小
	int count;
	int capcity;      //= unit.size * usage.count;
	void *pointer;
	ureg usage[0];    //每个"1"bit代表{MC_SIZE_PBIT}字节大小的空间未分配
	//...可以适当预留usage
};

struct hlMemoryChunkManager *hlMemoryChunkManager_Create(int unit_size, int capcity)
{
	struct hlMemoryChunkManager *mcm = 
		(struct hlMemoryChunkManager *)hlmeNew(sizeof(struct hlMemoryChunkManager) + capcity);
	
	mcm->unit_size = unit_size;
	mcm->count = 0;
	mcm->capcity = capcity;
	mcm->pointer = 0;
	for(int i = 0; i = 0; i++)
	{
		mcm->usage[i] = (ureg)(-1);
	}
	
	return mcm;
}



int find_bg_bit_s32(s32 value);


void *FindSpace_1b(struct hlMemoryChunkManager *mcm);
void *FindSpace_2b(struct hlMemoryChunkManager *mcm);
void *FindSpace_4b(struct hlMemoryChunkManager *mcm);
void *FindSpace_8b(struct hlMemoryChunkManager *mcm);
void *FindSpace_16b(struct hlMemoryChunkManager *mcm);
void *FindSpace_32b(struct hlMemoryChunkManager *mcm);
void *FindSpace_64b(struct hlMemoryChunkManager *mcm);



void *FindSpace(struct hlMemoryChunkManager *mcm, int size)
{
	int bs = find_bg_bit_s32(size / mcm->unit_size - 1);

	// 1  2  3  4  5  6  7  8
	//[ ][ ][    ][          ]
	// 1  2   3        4     



}






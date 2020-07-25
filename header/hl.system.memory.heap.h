#pragma once
#include <hl.type.h>
#include <hl.macro.bit.h>

/*

void hlmeAllocateHeap();
void hlmeReleaseHeap();


typedef void *hlHeap;


void hlmeNewH(hlHeap heap, t_size);

*/



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




//专为小内存分配设计的内存块管理器
struct hlMemoryChunkManager
{
	int unit_size;  //每个bit代表的字节大小
	int usage_count;
	int capcity;    //=unit.size * usage.count;
	void *pointer;
	ureg usage[0];
	//...可以适当预留usage
};


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






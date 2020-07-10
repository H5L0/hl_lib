#pragma once
#include <hl.type.h>

//#可以把这个放入hl.macro.h
#define return_if_null(pointer) if(pointer==NULL) return
#define return_null_if_null(pointer) if(pointer==NULL) return NULL
#define return_false_if_null(pointer) if(pointer==NULL) return NULL
#define return_false_if_false(expr) if(expr == FALSE) return FALSE



//--------------------------- Memory Allcation ------------------------------//

void *hlmeNew(t_size size);

void *hlmeNewClear(t_size size);

void *hlmeNewArray(t_size size_element, t_size length); //不会清零

void *hlmeNewCopy(const void *source, t_size size);

#define hlmeNewType(type) ((type*)hlmeNew(sizeof(type)))

#define HLME_NEW(type, name) type *name = (type *)hlmeNew(sizeof(type));


//传入NULL： 分配新空间
//传入有效空间：
//	调整大小失败：分配新空间
//	调整大小成功：返回原空间地址
void *hlmeResize(void *space, t_size newSize);


//传入NULL：返回FALSE
//传入有效空间：
//	调整大小失败：返回FALSE
//	调整大小成功：返回TRUE
Bool hlmeResizeOnly(void *space, t_size newSize);




Bool hlmeFree(void *space);	//return bool?

#define HLME_TRYFREE(space) if(space != NULL) hlmeFree(space);

//Bool hlmeTryFree(void *space);



//---------------------------- Memory Function ---------------------------//

void hlmeCopyR(void *destination, const void *source, t_size size);
void hlmeCopy(const void *source, void *destination, t_size size);

void hlmeFill(void *source, char ch, t_size count);

void hlmeClear(void *source, t_size size);

Bool hlmeIsEqual(const void *source1, const void *source2, t_size size);



void hlmeAllocateHeap();
void hlmeReleaseHeap();


typedef void *hlHeap;


void hlmeNewH(hlHeap heap, t_size);
















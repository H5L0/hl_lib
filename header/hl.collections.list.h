#if 0
#pragma once

#include <hl.type.h>
#include <hl.type.class.h>




typedef struct hlList
{
	void *_array;
	t_size capcity;
	t_size count;
}hlListT;


hlList *hlList_Create(t_size size_element, t_size capcity);



#define HLLIST_V(type, pList, index) (((type*)pList->_array)[index])


bool hlList_Add()



typedef struct hlListT
{
	hlType *type;
	void *_array;
	t_size capcity;
	t_size count;
}hlListT;




hlListT *hlListT_Create(hlType *type, t_size capcity);



hlListT *_hlListT_Resize(hlListT *list, t_size newCapcity);

void *hlListT_GetPointer(hlListT *list, t_size index);

bool hlListT_Set(hlListT *list, t_size index, void *pValue);

bool hlListT_Clear(hlListT *list);

bool hlListT_Release(hlListT *list);

void hlListT_To




#endif

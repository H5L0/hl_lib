#include <hl.type.h>


typedef struct hlType
{
	t_size size;

	void *(Copy)(void *source, void *target);

	u32 *(GetHash)();

}hlType;



extern hlType hlType_Int8;
extern hlType hlType_Int16;
extern hlType hlType_Int32;
extern hlType hlType_Int64;

extern hlType hlType_Half;
extern hlType hlType_Float;
extern hlType hlType_Double;





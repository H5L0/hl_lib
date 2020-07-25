#pragma once
#include <hl.macro.compile.h>

//=> hl.macro.builtin.h

//=>
//#define hl_builtin_allca(n) ...



HL_INLINE int hl_find_least_1(int value)
{
	return __builtin_ffs(value);
}








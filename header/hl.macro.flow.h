#pragma once


#define return_if_null(pointer) if(pointer==NULL) return
#define return_if_equal(value, exp, result) if(value == exp) return result

#define return_null_if_null(pointer) if(pointer==NULL) return NULL
#define return_null_if_negetive(value) if(value < 0) return NULL
#define return_null_if_n1(value) if(value == -1) return NULL

#define return_false_if_null(pointer) if(pointer==NULL) return NULL
#define return_false_if_false(expr) if(expr == FALSE) return FALSE

#define return_zero_if_null(p) if(p == NULL) return


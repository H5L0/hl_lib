#pragma once


//HL's inline function definition.
#define HL_INLINE static inline


#define BIT(n) (1 << n)

#define SET_BIT(value, n) (value |= (1 << n))
#define CLEAR_BIT(value, n) (value &= ~(1 << n))




#define ISNULL(var) (var==0)


//Does var have flag?
#define HASFLAG(var,flag)	((var & flag) != 0)
//Does var have all these flags?
#define HASFLAGS(var,flags)	((var & flags) == flags)

//The var contains this flag.
#define NOFLAG(var,flag)	((var & flag) == 0)
//The var does not contain all these flags.
#define NOFLAGS(var,flags)	((var & flags) != flags)



//class
//FC_RETURN
//FC_ARGS



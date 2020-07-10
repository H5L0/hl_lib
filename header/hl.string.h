#pragma once
#include <hl.type.h>


typedef char hlChar8;
typedef u16 hlChar16;
typedef u32 hlChar32;

typedef hlChar8 c8;
typedef hlChar16 c16;
typedef hlChar32 c32;

typedef hlChar8  hlCharA;
typedef hlChar32 hlChar;


typedef struct hlStringA hlStringA;
typedef struct hlString hlString;


//ascii string
struct hlStringA{
	hlChar8 *chars;
	int length;		//***u32
};

//utf-32 string
struct hlString{
	hlChar32 *chars;
	int length;
};


//-------------------------*hlsa*----------------------//

hlStringA *hlsaNew();

Bool hlsaFree(hlStringA *str);

hlStringA *hlsaCopyChars(hlStringA *str, const char *chars);

hlStringA *hlsaCopyCharsInLen(hlStringA *str, const char *chars, int length);

hlStringA *hlsaCopy(hlStringA *target, const hlStringA *source);

hlStringA *hlsaTrim(hlStringA *target, const hlStringA *source, int start, int length);


hlStringA *hlsaConnect(hlStringA *outstr, const hlStringA *str1, const hlStringA *str2);

hlStringA *hlsaInsert(hlStringA *outstr, const hlStringA *str, const hlStringA* word, int pos);

hlStringA *hlsaPlace(hlStringA *outstr, const hlStringA *str, const hlStringA* word, int pos);

hlStringA *hlsaReplace(hlStringA outstr, const hlStringA *str, const hlStringA *word, int pos, int length);



int *hlsaFindChar(const hlStringA *str, char ch);

int *hlsaFindChars(const hlStringA *str, const char * chars);

int *hlsaFind(const hlStringA *str, const hlStringA *word);

//FindLast
//FindAll

Bool hlsaStartWithChars(const hlStringA *str, const char *chars);

Bool hlsaStartWith(const hlStringA *str, const hlStringA *word);


Bool hlsaEndWithChars(const hlStringA *str, const char *chars);

Bool hlsaEndWith(const hlStringA *str, const hlStringA *word);


//hlArray *hlsaSplit

int hlsaSplit(hlStringA ** pArray, const hlStringA *str, char separator);





char *hlsaAt(hlStringA *str, int index); //= str.chars[index]

int hlsaLength(hlStringA *str);

int hlGetCharsLength(const char *chars);


//*---------------*//

hlStringA *hlsNewNullA();

hlStringA *hlsNewA(const char *source);

hlStringA *hlsNewByLengthA(const char *source, int length);

hlStringA *hlsNewCopyA(const hlStringA *str);

hlStringA *hlsCopyA(hlStringA *target, const hlStringA *source);

hlStringA *hlsTrim(const hlStringA *str, int start, int length);

hlCharA *hlsAt(hlStringA *str, int index);
















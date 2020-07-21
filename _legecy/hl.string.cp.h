

#define HL_LIB_SUPPORT_UTF8 0





typedef struct hlChars
{
	int length;
	char array[0];
}hlChars;


#include <hl.chars.h>
#include <hl.system.memory.h>


hlChars *hlcNewNull(int length)
{
	return (hlChars *)hlmeNew(sizeof(hlChars) + sizeof(char) * length);
}

bool hlcFree(hlChars *cs)
{
	return (bool)hlmeFree(cs);
}


hlChars *hlcNewLengthA(char *chars, int length)
{
	hlChars *cs = hlcNewNull(length);
	hlmeCopy(chars, cs->array, length);
	return cs;
}


hlChars *hlcNewLength(hlChars *cs, int length)
{
	int len = length < cs->length ? length : cs->length;
	return hlcNewLengthA(cs->array, len);
}


hlChars *hlcNewA(char *chars)
{
	int len = hl_chars_length_clamp(chars, 4096);
	return hlcNewLengthA(chars, len);
}

hlChars *hlcNew(hlChars *cs)
{
	return hlcNewLengthA(cs->array, cs->length);
}


hlChars *hlcConnect(hlChars *c1, hlChars *c2)
{
	hlChars *cs = hlcNewNull(c1->length + c2->length);
	hlmeCopy(c1->array, cs->array, c1->length);
	hlmeCopy(c1->array, cs->array + c1->length, c2->length);
	return cs;
}

hlChars *hlcInsert(hlChars *source, hlChars *word);

























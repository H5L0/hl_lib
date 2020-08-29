

#include <hl.string.h>
#include <hl.chars.h>
#include <hl.memory.h>


bool _hlsaResize(hlStringA *str, int newLength)
{
	++newLength;
	//NULL/Failed
	if(!hlmeResizeOnly(str->chars, newLength))
	{
		//分配新内存
		str->chars = hlmeNew(newLength);	
		//分配是否成功
		if(str->chars == NULL) return FALSE;
	}
	
	str->length = newLength;
	return TRUE;
}



hlStringA *hlsaNew()
{
	HLME_NEW(hlStringA, str);
	str->chars = NULL;
	str->length = 0;
	return str;
}

hlStringA *hlsaNewCopy(const char *chars)
{
	HLME_NEW(hlStringA, str);
	str->length = 0;
	if(hlsaCopyChars(str, chars)) return str;
	else return NULL;
}


hlsaResult hlsaFree(hlStringA *str)
{
	Bool r1 = str->chars ? hlmeFree(str->chars) : TRUE;
	Bool r2 = hlmeFree(str);
	if(r1 && r2) return hlsaSuccess;
	else return hlsaFailed;
}


hlsaResult hlsaCopyChars(hlStringA *str, const char *chars)
{
	int length = hl_chars_length(chars);
	return hlsaCopyCharsInLen(str, chars, length);
}


hlsaResult hlsaCopyCharsInLen(hlStringA *str, const char *chars, int length)
{
	if(length < 0) return hlsaFailed;

	//目标长度小于或大于两倍源长度的情况下，重新分配内存
	//if(str->length < length || str->length > length * 2) 
	//{
		if(_hlsaResize(str, length)==FALSE) return hlsaFailed;
	//}
	
	//复制内容
	hlmeCopy(chars, str->chars, length + 1);
	//str->length = length;
	return hlsaSuccess;
}


hlsaResult hlsaCopy(hlStringA *des, const hlStringA *src)
{
	return hlsaCopyCharsInLen(des, src->chars, src->length);
}


hlsaResult hlsaTrim(hlStringA *des, const hlStringA *src, int start, int length)
{
	if(start >= src->length) return hlsaFailed;
	if(start + length > src->length) length = src->length - start;

	return hlsaCopyCharsInLen(des, src->chars + start, length);
}


hlsaResult hlsaConnect(hlStringA *outstr, const hlStringA *str1, const hlStringA *str2)
{
	int slen =  str1->length + str2->length;	
	if(!_hlsaResize(outstr, slen)) return hlsaFailed;

	outstr->length = slen;
	hlmeCopy(str1->chars, outstr->chars, str1->length);
	hlmeCopy(str2->chars, outstr->chars + str1->length, str2->length);
	return hlsaSuccess;
}



hlsaResult hlsaInsert(hlStringA *outstr, const hlStringA *str, const hlStringA* word, int pos)
{
	if(pos > str->length) pos = str->length;

	int slen = str->length + word->length;
	if(!_hlsaResize(outstr, slen)) return hlsaFailed;

	hlmeCopy(str->chars, outstr->chars, pos);
	hlmeCopy(word->chars, outstr->chars + pos, word->length);
	hlmeCopy(str->chars + pos, outstr->chars + pos + word->length, str->length - pos);

	return hlsaSuccess;
}

hlsaResult hlsaPlace(hlStringA *outstr, const hlStringA *str, const hlStringA* word, int pos);

hlsaResult hlsaReplace(hlStringA outstr, const hlStringA *str, const hlStringA *word, int pos, int length);



int hlsaFindChar(const hlStringA *str, char ch);

int hlsaFindChars(const hlStringA *str, const char * chars);

int hlsaFind(const hlStringA *str, const hlStringA *word);

//FindLast
//FindAll

Bool hlsaStartWithChars(const hlStringA *str, const char *chars);

Bool hlsaStartWith(const hlStringA *str, const hlStringA *word);


Bool hlsaEndWithChars(const hlStringA *str, const char *chars);

Bool hlsaEndWith(const hlStringA *str, const hlStringA *word);


//hlArray *hlsaSplit

int hlsaSplit(hlStringA ** pArray, const hlStringA *str, char separator);





char hlsaAt(hlStringA *str, int index)
{
	//if(str == NULL || str->chars == NULL) return '\0';
	return str->chars[index];
}

int hlsaLength(hlStringA *str)
{
	//if(str == NULL || str->chars == NULL) return 0;
	return str->length;
}




















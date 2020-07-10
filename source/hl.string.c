

#include <hl.string.h>
#include <hl.system.memory.h>



int hlGetCharsLength(const char *chars)
{
	int len = 0;
	while (*chars != '\0') { len++; chars++; }
	return len;
}


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



Bool hlsaFree(hlStringA *str)
{
	//return_false_if_null(str); 
	if(str->chars != NULL) hlmeFree(str->chars);
	hlmeFree(str);
	return TRUE;
}


hlStringA *hlsaCopyChars(hlStringA *str, const char *chars)
{
	int length = hlGetCharsLength(chars);
	return hlsaCopyCharsInLen(str, chars, length);
}


hlStringA *hlsaCopyCharsInLen(hlStringA *str, const char *chars, int length)
{
	if(length < 0) return NULL;	

	//目标长度小于或大于两倍源长度的情况下，重新分配内存
	//if(str->length < length || str->length > length * 2) 
	//{
		if(_hlsaResize(str, length)==FALSE) return NULL;
	//}
	
	//复制内容
	hlmeCopyR(str->chars, chars, length + 1);
	//str->length = length;
	return str;
}


hlStringA *hlsaCopy(hlStringA *des, const hlStringA *src)
{
	return hlsaCopyCharsInLen(des, src->chars, src->length);
}


hlStringA *hlsaTrim(hlStringA *des, const hlStringA *src, int start, int length)
{
	if(start >= src->length) return NULL;
	if(start + length > src->length) length = src->length - start;

	return hlsaCopyCharsInLen(des, src->chars + start, length);
}


hlStringA *hlsaConnect(hlStringA *outstr, const hlStringA *str1, const hlStringA *str2)
{
	int slen =  str1->length + str2->length;	
	if(!_hlsaResize(outstr, slen)) return NULL;

	outstr->length = slen;
	hlmeCopyR(outstr->chars, str1->chars, str1->length);
	hlmeCopyR(outstr->chars + str1->length, str2->chars, str2->length);
	return outstr;
}



hlStringA *hlsaInsert(hlStringA *outstr, const hlStringA *str, const hlStringA* word, int pos)
{
	if(pos > str->length) pos = str->length;

	int slen = str->length + word->length;
	if(!_hlsaResize(outstr, slen)) return NULL;

	hlmeCopyR(outstr->chars, str->chars, pos);
	hlmeCopyR(outstr->chars + pos, word->chars, word->length);
	hlmeCopyR(outstr->chars+ pos + word->length, str->chars + pos, str->length - pos);

	return outstr;
}

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




















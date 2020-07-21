#include <hl.string.format.h>
#include <hl.chars.format.h>


/*
int hlsFormat(char *buffer, int bsize, const char *format, const char *types, ...)
{
	if(format == NULL || *format == '\0') return 0;
	if(types == NULL)
	{
		//copy to buffer directly.
	}

	void *vlist = &types + _XLEN;

	return strf_vargs(buffer, buffer + bsize, format, types, vlist);
}
*/


hlStringA *hlsFormat(const char *format, ...)
{
	hlStringA *str = hlsaNew();
	if(format == NULL || *format == '\0') return str;

	va_list list;
	va_start(list, format);

	const int bsize = 4096;
	char buffer[bsize];

	int rcount = hlcf_vlist(buffer, buffer + bsize, format, list);

	hlsaCopyCharsInLen(str, buffer, rcount);

	return str;
}




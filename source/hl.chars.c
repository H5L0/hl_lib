#include <hl.chars.h>




int hl_chars_length(const char *chars)
{
	int len = 0;
	while (*chars != '\0') { len++; chars++; }
	return len;
}





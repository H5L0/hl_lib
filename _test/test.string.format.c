#include <stdio.h>
#include <stdlib.h>


typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned char bool;
#define TRUE  1
#define FALSE 0
//#define NULL 0


int strf_integer_align_left(
	char *buffer, u32 bSize,
	const char *format,
	const char *raws,
	bool negetive)
{
	char *pbuf = buffer;
	char c;

	do {
		c = *(format++);
		switch(c)
		{
			case '-': *(pbuf++) = *raws == '\0' ? '0' : *(raws++); break;
			case '_': *(pbuf++) = *raws == '\0' ? ' ' : *(raws++); break;
			case '@': if(negetive) *(pbuf++) = '-';
			case '*':
				while((c = *raws) != '\0')
				{
				*(pbuf++) = c;
				++raws;
				}
				break;
			case '?':
				if(*format == '=')
				{
					++format;
					if(negetive)
					{
						*(pbuf++) = '-';
						c = *format;
						if(c == '\0') goto end;
						else if(c!='*'||c!='@') ++format;
					}
				}
				else *(pbuf++) = negetive ? '-' : '+';
				break;
			case '|': continue;
			case '\0': goto end;
			default: *(pbuf++) = c;
		}
/*

		if(c=='-')
		{
			if(*raws == '\0') *(pbuf++) = '0';
			else *(pbuf++) = *(raws++);
		}
		else if(c=='_')
		{
			if(*raws == '\0') *(pbuf++) = ' ';
			else *(pbuf++) = *(raws++);
		}
		else if(c=='*')
		{
			while((c = *raws) != '\0')
			{
				*(pbuf++) = c;
				++raws;
			}
		}
		else if(c=='@')
		{
			if(negetive) *(pbuf++) = '-';
			while((c = *raws) != '\0')
			{
				*(pbuf++) = c;
				++raws;
			}
		}
		else if(c=='?')
		{
			if(negetive)
			{
				*(pbuf++) = '-';
				if(*format=='=')
				{
					c = *(++format);
					if(c == '*');
					else if(c == '\0') break;
					else ++format;
				}
			}
			else
			{
				if(*format=='=') format += 1;
				else *(pbuf++) = '+';
			}
		}
		else if(c=='|')
		{
			continue;
		}
		else if(c=='\0')
		{
			break;
		}
		else
		{
			*(pbuf++) = c;
		}*/

	} while(TRUE);

end:
	(*pbuf) = c;
	return (int)(pbuf - buffer);
}


int strf_integer_align_right(
	char *buffer, u32 bSize,
	const char *format, //u32 fSize,
	const char *raws, //u32 rSize,
	bool negetive)
{
	char *pbuf = buffer + bSize;
	const char *pfmt = format;
	const char *praw = raws;
	while(*pfmt!='\0') ++pfmt;
	while(*praw!='\0') ++praw;

	do {
		char c = *(--pfmt);
		switch(c)
		{
			case '-': *(--pbuf) = (praw == raws) ? '0': *(--praw); break;
			case '_': *(--pbuf) = (praw == raws) ? ' ': *(--praw); break;
			case '@': break;
			case '*':
				while(praw != raws)
				{
					*(--pbuf) = *(--praw);
				}
				break;
			case '?':
				if(*(pfmt+1)=='=')
				{
					if(negetive)
					{
						if(pbuf == buffer + bSize) *(--pbuf) = '-';
						else *pbuf = '-';	//******
					}
				}
				else *(--pbuf) = negetive ? '-': '+';
				break;
			case '|': continue;
			case '=': continue;
			default: *(--pbuf) = c;
		}
	} while(pfmt != format);

	int n = buffer + bSize - pbuf;
	const char *end = buffer + n;
	while(buffer != end) *(buffer++) = *(pbuf++);
	*(buffer) = '\0';
	return n;
}


int strf_integer_format(
	char *buffer, u32 bSize,
	const char *format,
	const char *raws,
	bool negetive)
{
	/*
	char align = 0;
	if(format != NULL)
	{
		if(*format=='|')
		{
			align = -1;
			format++;
		}
		if(*format == '\0')
		{
			align = 0;
		}
	}
	
	if     (align == 0) return strf_integer_align_left (buffer, bSize, "*",    raws, negetive);
	else if(align == 1) return strf_integer_align_right(buffer, bSize, format, raws, negetive);
	else                return strf_integer_align_left (buffer, bSize, format, raws, negetive);
	*/

	if(format != NULL)
	{
		if(*format == '|')
		{
			format++;
			if(format == '\0') goto L_int_align_default;
			else return strf_integer_align_left(buffer, bSize, format, raws, negetive);
		}
		else if(*format == '\0') goto L_int_align_default;
		else return strf_integer_align_right(buffer, bSize, format, raws, negetive);
	}
	L_int_align_default:
	return strf_integer_align_left(buffer, bSize, "*", raws, negetive);
}




int strf_string_align_left(
	char *buffer, u32 bSize,
	const char *format,
	const char *raws,
	bool negetive)
{
	char *pbuf = buffer;
	char c;

	do {
		c = *(format++);
		if(c=='-' || c=='_')
		{
			*(pbuf++) = *raws == '\0' ? ' ' : *(raws++);
		}
		else if(c=='*' || c=='@')
		{
			while((c = *raws) != '\0')
			{
				*(pbuf++) = c;
				++raws;
			}
		}
		else if(c=='|') continue;
		else if(c=='\0') break;
		else
		{
			*(pbuf++) = c;
		}
	} while(TRUE);

	(*pbuf) = c;
	return (int)(pbuf - buffer);
}


int strf_string_align_right(
	char *buffer, u32 bSize,
	const char *format,
	const char *raws,
	bool negetive)
{
	char *pbuf = buffer + bSize;
	const char *pfmt = format;
	const char *praw = raws;
	while(*pfmt!='\0') ++pfmt;
	while(*praw!='\0') ++praw;

	do {
		char c = *(--pfmt);
		switch(c)
		{
			case '-':
			case '_': *(--pbuf) = (praw == raws) ? ' ': *(--praw); break;
			case '@':
			case '*': while(praw != raws){ *(--pbuf) = *(--praw); } break;
			case '|': continue;
			default: *(--pbuf) = c;
		}

		/*
		if(c=='-' || c=='_')
		{
			*(--pbuf) = (praw == raws) ? ' ': *(--praw);
		}
		else if(c=='*' || c=='@')
		{
			while(praw != raws)
			{
				*(--pbuf) = *(--praw);
			}
		}
		else if(c=='|') continue;
		else
		{
			*(--pbuf) = c;
		}
		*/

	} while(pfmt != format);

	int n = buffer + bSize - pbuf;
	const char *end = buffer + n;
	while(buffer != end) *(buffer++) = *(pbuf++);
	*(buffer) = '\0';
	return n;
}




int strf_u32(char *buffer, u32 bSize, const char *format, u32 value)
{
	char raws[12];
	char *praw = raws + 11;
	*praw = '\0';
	while(value != 0)
	{
		u32 n = value % 10;
		value = value / 10;
		*(--praw) = n + '0';
	}
	return strf_integer_format(buffer, bSize, format, praw, FALSE);
}

int strf_s32(char *buffer, u32 bSize, const char *format, s32 value)
{
	bool negetive = FALSE;
	if(value < 0)
	{
		negetive = TRUE;
		value = -value;
	}

	char raws[12];
	char *praw = raws + 11;
	*praw = '\0';

	while(value != 0)
	{
		u32 n = value % 10;
		value = value / 10;
		*(--praw) = n + '0';
	}
	return strf_integer_format(buffer, bSize, format, praw, negetive);
}


int strf_float(char *buffer, u32 bSize, const char *format, float value)
{
	//bool negetive = value < 0;
	u64 iv = (int)(value < 0 ? -value : value);

	char iraws[16];
	char fraws[8];	
	char *praw = iraws;
	while(iv != 0)
	{
		*(praw++) = (iv % 10) + '0';
		iv /= 10;
	}
	*praw = '\0';

	for(int i = 0; i < 7; i++)
	{
		value *= 10;
		fraws[i] = ((u32)value % 10) + '0';
	}
	fraws[7]='\0';

	printf("i: %s\n", iraws);
	printf("f: %s\n", fraws);

	return 0;
}









int main()
{
	//s32 value = -123;
	//const char *format = "?=_____|"; //=='@'

	char buffer[64];
	//int count = strf_u32(buffer, 64, format, value);
	//int count = strf_s32(buffer, 64, format, value);

	//int count = strf_integer_align_left(format, buffer, 64, "1234", TRUE);

	//char *buffer, u32 bSize, const char *format, u32 fSize, const char *raws, u32 rSize, bool negetive
	//int count = strf_integer_align_right(buffer, 64, format, "1234", FALSE);

	//printf("count:%d\n", count);
	//printf("|%s|\n", buffer);

	strf_float(buffer, 64, NULL, 1234.5678f);

	//while(value < 30000000)
	{
		//strf_s32(buffer, 64, format, value);
		//sprintf(buffer, "%8.5d", value);
		//sprintf(buffer, "%8.5d", value);
		//++value;
	}
	printf("\n");
	return 0;
}



#include <hl.string.format.h>




int strf_integer_align_left(
	char *buffer,
	char *buffer_end,
	const char *format,
	const char *format_end,
	const char *raws,
	bool negetive)
{
	char *pbuf = buffer;
	char c;

	while(format != format_end)
	{
		c = *(format++);
		if      (c == '-') *(pbuf++) = *raws == '\0' ? '0' : *(raws++);
		else if (c == '_') *(pbuf++) = *raws == '\0' ? ' ' : *(raws++);
		else if (c == '@')
		{
			if (negetive)
				*(pbuf++) = '-';
		}
		else if (c == '*')
		{
			while ((c = *raws) != '\0')
			{
				*(pbuf++) = c;
				++raws;
			}
		}
		else if (c == '?')
		{
			if (*format == '=')
			{
				++format;
				if (negetive)
				{
					*(pbuf++) = '-';
					if(format == format_end)
						goto end;
					c = *format;
					if (c != '*' || c != '@')
						++format;
				}
			}
			else
				*(pbuf++) = negetive ? '-' : '+';
		}
		else if (c == '|')
			continue;
		else
			*(pbuf++) = c;
	}

end:
	(*pbuf) = '\0';
	return (int)(pbuf - buffer);
}


int strf_integer_align_right(
	char *buffer,
	char *buffer_end,
	const char *format,
	const char *format_end,
	const char *raws,
	//raws_end,
	bool negetive)
{
	char *pbuf = buffer_end;
	const char *pfmt = format_end;
	const char *praw = raws;
	while (*praw != '\0')
		++praw;

	while (pfmt != format)
	{
		char c = *(--pfmt);
		switch (c)
		{
		case '-':
			*(--pbuf) = (praw == raws) ? '0' : *(--praw);
			break;
		case '_':
			*(--pbuf) = (praw == raws) ? ' ' : *(--praw);
			break;
		case '@':
			break;
		case '*':
			while (praw != raws)
			{
				*(--pbuf) = *(--praw);
			}
			break;
		case '?':
			if (*(pfmt + 1) == '=')
			{
				if (negetive)
				{
					if (pbuf == buffer_end)
						*(--pbuf) = '-';
					else
						*pbuf = '-'; //******
				}
			}
			else
				*(--pbuf) = negetive ? '-' : '+';
			break;
		case '|':
			continue;
		case '=':
			continue;
		default:
			*(--pbuf) = c;
		}
	}

	int n = buffer_end - pbuf;
	const char *end = buffer + n;
	while (buffer != end)
		*(buffer++) = *(pbuf++);
	*(buffer) = '\0';
	return n;
}

int strf_integer_format(
	char *buffer,
	char *buffer_end,
	const char *format,
	const char *format_end,
	const char *raws,
	bool negetive)
{
	if(format != NULL && *format != '\0')
	{
		if (*format != '|')
			return strf_integer_align_right(buffer, buffer_end, format, format_end, raws, negetive);
		else
			++format;
	}
	else 
	{
		format = "*";
		format_end = format + 1;
	}

	//format == NULL || format[0] =='\0' || format[0] == '|'
	return strf_integer_align_left(buffer, buffer_end, format, format_end, raws, negetive);
}



int strf_u32(char *buffer, char *b_end, const char *format, const char *f_end, u32 value)
{
	char raws[12];
	char *praw = raws + 11;
	*praw = '\0';
	while (value != 0)
	{
		u32 n = value % 10;
		value = value / 10;
		*(--praw) = n + '0';
	}
	return strf_integer_format(buffer, b_end, format, f_end, praw, FALSE);
}


int strf_s32(char *buffer, char *b_end, const char *format, const char *f_end, s32 value)
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
	return strf_integer_format(buffer, b_end, format, f_end, praw, negetive);
}



char *S32ToString(const char *format, s32 value);

char *U64ToString(const char *format, u64 value);

char *S64ToString(const char *format, s64 value);

char *HexToString(ureg value);

char *FloatToString(float value);

char *DoubleToString(double value);







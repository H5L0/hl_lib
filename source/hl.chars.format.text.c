#include <hl.chars.format.h>


int hlcf_text_align_left(
	char *buffer,
	char *buffer_end,
	const char *format,
	const char *format_end,
	const char *chars,
	const char *chars_end
	)
{
	char *pbuf = buffer;

	while(format != format_end)
	{
		char c = *(format++);
		if (c == '_')
		{
			*(pbuf++) = (chars == chars_end) ? ' ' : *(chars++);
		}
		else if (c == '*')
		{
			while (chars != chars_end)
			{
				*(pbuf++) = *(chars++);
			}
		}
		else if (c == '|')
			continue;
		else
			*(pbuf++) = c;
	}

	(*pbuf) = '\0';
	return (int)(pbuf - buffer);
}


int hlcf_text_align_right(
	char *buffer,
	char *buffer_end,
	const char *format,
	const char *format_end,
	const char *chars,
	const char *chars_end
	)
{
	char *pbuf = buffer_end;

	while (format_end != format)
	{
		char c = *(--format_end);
		if(c == '_')
		{
			*(--pbuf) = (chars_end == chars) ? ' ' : *(--chars_end);
		}
		else if(c == '*')
		{
			while (chars_end != chars)
			{
				*(--pbuf) = *(--chars_end);
			}
		}
		else if(c == '|')
			continue;
		else
			*(--pbuf) = c;
	}

	int n = buffer_end - pbuf;
	const char *end = buffer + n;
	while (buffer != end)
		*(buffer++) = *(pbuf++);

	*(buffer) = '\0';
	return n;
}


//int hlcf_text(
int hlcf_str(
	char *buffer,
	char *buffer_end,
	const char *format,
	const char *format_end,
	const char *chars
	)
{
	const char *chars_end = chars;
	while(*chars_end != '\0') chars_end++;

	if(format != NULL && *format != '\0')
	{
		if (*format == '|') ++format;
		else return hlcf_text_align_right(buffer, buffer_end, format, format_end, chars, chars_end);
	}
	else 
	{
		format = "*";
		format_end = format + 1;
	}

	//format == NULL || format[0] =='\0' || format[0] == '|'
	return hlcf_text_align_left(buffer, buffer_end, format, format_end, chars, chars_end);
}



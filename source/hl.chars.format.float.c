
#include <hl.chars.format.h>



int hlcf_float_raw
(
	char *buffer,
	char *buffer_end,
	const char *format,
	const char *format_end,
	const char *ints,
	const char *floats,
	bool negetive
)
{
	"float is {?=--.--}";

	if(floats == NULL)
	{
		"123";
	}
	if(floats == "0")
	{
		"123.0";
	}

	for(const char *pfmt = format; pfmt != format_end; pfmt++)
	{
		if(*pfmt == '.')
		{
			break;
		}
	}

	int len1 = 0;
	int len2 = 0;
	if(pfmt - format > 1)
	{
		len1 = hlcf_integer_align_right(buffer, buffer_end, format, pfmt, ints, negative);
	}
	if(format_end - pfmt > 1)
	{
		len2 = hlcf_integer_aligg_left(buffer+len1, buffer_end, pfmt + 1, format_end, floats, negative);
	}

	return len1 + len2;
}





int hlcf_f32(char *buffer, char *b_end, const char *format, const char *f_end, float value)
{
	bool negative = value < 0;
	if(negative) value =-value;

	u64 ivalue = (u64)value;
	value = value - ivalue;

	char ints[24];
	char *pint = ints;
	while (value != 0)
	{
		char n = ivalue % 10;
		ivalue = ivalue / 10;
		*(pint++) = n + '0';
	}
	*praw = '\0';

	char floats[12];
	char *pfloat = floats;
	while (float != 0)
	{
		value *= 10;
		char n = (int)(value);
		value = value - n;
		*(pfloat++) = n + '0';
	}
	*pfloat = '\0';





	return hlcf_float_raw(buffer, b_end, format, f_end, ints, floats, negative);
}

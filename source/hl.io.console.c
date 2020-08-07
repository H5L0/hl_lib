#include <hl.io.console.h>
#include <hl.io.standard.h>

#include <hl.chars.h>
#include <hl.chars.format.h>



bool _hlcs_have_init = FALSE;


Bool hlcsInit()
{
	if(_hlcs_have_init)
	{
		return FALSE;
	}
	else
	{
		_hlcs_have_init = hlInitStdStreams();
		return _hlcs_have_init;
	}
}


Bool hlcsFlush()
{
	return hltwFlush(hl_std_output);
}


Bool hlcsRelease()
{
	hlcsFlush();

	hltwRelease(hl_std_output);
	hl_std_output = NULL;

	return TRUE;
}




int hlcsWriteA(const char *format, ...)
{
	va_list list;
	va_start(list, format);

	return hltwWriteFormatVA(hl_std_output, format, list);
}


int hlcsWriteLineA(const char *format, ...)
{
	va_list list;
	va_start(list, format);

	return hltwWriteLineFormatVA(hl_std_output, format, list);
}



int hlcsReadA(char *buffer, int size)
{
	if(size == 0) return 0;
	int rcount = hltrReadA(hl_std_input, buffer, size - 1);
	buffer[rcount + 1] = '\0';
	return rcount;
}

int hlcsReadLineA(char *buffer, int buffer_size)
{
	if(buffer_size == 0) return 0;
	int rcount = hltrReadLineA(hl_std_input, buffer, buffer_size - 1);
	buffer[rcount + 1] = '\0';
	return rcount;
}


int hlcsReadChar()
{
	return hltrReadCharA(hl_std_input);
}
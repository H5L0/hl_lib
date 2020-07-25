#include <hl.io.console.h>
#include <hl.io.stream.h>
#include <hl.io.filestream.h>
#include <hl.io.textstream.h>
//#include <hl.kernel.io.h>

#include <hl.chars.h>
#include <hl.chars.format.h>

#include <hl.macro.vargs.h>

#include <hl.system.memory.h>



bool _hlcs_have_init = FALSE;

hlTextWriter *hl_std_output;   //stream hl_output
hlTextReader  *hl_std_input;    //stream hl_input
hlTextWriter *hl_std_error;    //stream hl_error




Bool hlcsInit()
{
	if(_hlcs_have_init) return FALSE;

	//Create file.
	//hlFile *f_stdout = hlfOpenStandard("");
	hlFile *f_stdout = hlmeNewType(hlFile);
	f_stdout->id = 0;

	hlFile *f_stdin = hlmeNewType(hlFile);
	f_stdin->id = 1;

	//Create text writer from file writer.
	hl_std_output = hltwCreateFromFile(f_stdout);
	hltwSetFlushMode(hl_std_output, em_tsflush_line);

	hl_std_input = hltrCreateFromFile(f_stdin);

	return TRUE;
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
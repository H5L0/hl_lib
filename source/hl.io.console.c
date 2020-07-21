#include <hl.io.console.h>
#include <hl.chars.h>
#include <hl.chars.format.h>
#include <hl.kernel.io.h>


#include <hl.macro.vargs.h>

//hl_console_write_buffer();
//hl_console_write_direct();


/*
int hlcsWriteVA(const char *format, const char *types, void **args)
{
	//void ** args_array[32];
	//va_list list;
	//list->

	if(format == NULL || *format == '\0') return 0;
	if(types == NULL) return hl_file_write(0, format, hl_chars_length(format) + 1);

	char buffer[4096];

	int count = strf_vargs(buffer, buffer + 4096, format, types, args);

	return hl_file_write(0, buffer, count);
}
*/


hlStream *_hl_stdout;
hlStream *_hl_stdin;
hlstream *_hl_stderror;



int hlcsWriteA(const char *format, ...)
{
	if(format == NULL || *format == '\0') return 0;

	va_list list;
	va_start(list, format);

	char buffer[4096];
	int count = hlcf_vlist(buffer, buffer + 4096, format, list);

	//return hl_file_write(0, buffer, count);

	int lastEnter = FindLastEnter();

	if(lastEnter != -1)
	{
		int wcount1 = hlfsWrite(_hl_stdout, buffer, lastEnter);
		hlfsFlush(_hl_stdout);
	}

	int wcount2 = hlfsWrite(_hl_stdout, buffer + lastEnter, count - lastEnter);
	return wcount1 + wcount2;
}


int hlcsWriteLineA(const char *format, ...)
{
	if(format == NULL || *format == '\0') return 0;

	va_list list;
	va_start(list, format);

	char buffer[4096];
	int count = hlcf_vlist(buffer, buffer + 4096, format, list);

	if(count == 4096) buffer[4095] = '\n';
	else buffer[count] = '\n';

	//return hl_file_write(0, buffer, count);

	int wcount = hlfsWrite(_hl_stdout, buffer + lastEnter, count - lastEnter);
	hlfsFlush(_hl_stdout);
	return wcount;
}


char *hlcsReadLineNA()
{
	return 0;
}

int hlcsReadLineA(char *buffer, int bsize)
{
	--bsize;
	int rcount = 0;
	char ch;
	do
	{
		int rs =  hl_file_read(1, &ch, 1);
		//if(rs == -1)

		if(ch == '\n') break;

		buffer[rcount++] = ch;
	} while (rcount != bsize);		//应该抛弃换行符前的字符吗

	buffer[rcount] = '\0';
	return rcount;
}


int hlcsReadChar()
{
	char ch;
	int rcount = hl_file_read(1, &ch, 1);

	if(rcount != 1) return 0;
	else return ch;
}

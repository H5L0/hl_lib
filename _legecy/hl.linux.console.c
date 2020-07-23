/*

#include <hl.linux.console.h>
#include <hl.linux.syscall.h>


int _hl_std_input;
int _hl_std_output;
int _hl_std_error;



int hl_console_redirect(int type, int new_stream)
{
	
}


int hl_console_write(const char *text)
{
	sys_write(_hl_std_output, text, xx);
}


int hl_console_read(const char *buffer)
{
	sys_read(_hl_std_input, format, xx);
}


*/





struct hlWriteStream *hl_std_output;   //stream hl_output
struct hlReadStream  *hl_std_input;    //stream hl_input
struct hlWriteStream *hl_std_error;    //stream hl_error


Bool hlcsInit()
{
	hlFile *f_stdout = hlfOpenStandard();
	hl_std_output = hlfwCreate(f_stdout);

	//hl_std_output = hltwCreate(fs_stdout);
}



int hlcsWriteA(const char *format, ...)
{
	if(format == NULL || *format == '\0') return 0;

	va_list list;
	va_start(list, format);

	char buffer[4096];
	int count = hlcf_vlist(buffer, buffer + 4096, format, list);

	return hl_std_output->Write(hl_std_output, buffer, count);

	/*
	int lastEnter = FindLastEnter();

	if(lastEnter != -1)
	{
		int wcount1 = hlfsWrite(_hl_stdout, buffer, lastEnter);
		hlfsFlush(_hl_stdout);
	}

	int wcount2 = hlfsWrite(_hl_stdout, buffer + lastEnter, count - lastEnter);
	return wcount1 + wcount2;
	*/

}


int hlcsWriteLineA(const char *format, ...)
{
	if(format == NULL || *format == '\0') return 0;

	va_list list;
	va_start(list, format);

	char buffer[4096];
	int count = hlcf_vlist(buffer, buffer + 4096, format, list);

	if(count == 4096) buffer[4095] = '\n';
	else buffer[count++] = '\n';

	return hl_std_output->Write(hl_std_output, buffer, count);

	/*
	_hl_stdout->WriteLineFormatVA(_hl_stdout, format, list);
	//_hl_stdout->Write(_hl_stdout, buffer, count);

	_hl_stdout->Flush(_hl_stdout);
	return count;

	//int wcount = hlfsWrite(_hl_stdout, buffer + lastEnter, count - lastEnter);
	//hlfsFlush(_hl_stdout);
	*/
}


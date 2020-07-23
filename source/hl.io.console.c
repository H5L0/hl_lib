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
	hlFile *f_stdout = (hlFile*)hlmeNew(sizeof(hlFile));
	f_stdout->id = 0;

	//Create file writer.
	//hlFileWriter *fw_stdout = hlfwCreate(f_stdout);

	//Create text writer from file writer.
	hl_std_output = hltwCreateFromFile(f_stdout);
	hl_std_output->flush_mode = em_tsflush_line;

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


/*

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


*/
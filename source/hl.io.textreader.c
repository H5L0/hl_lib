
#include <hl.io.textstream.h>
#include <hl.system.memory.h>

#include <hl.chars.h>
#include <hl.chars.format.h>

#include <hl.macro.vargs.h>



hlTextReader *hltrCreate(struct hlReadStream *rstream)
{
	hlTextReader *tr = hlmeNewType(hlTextReader);
	return_null_if_null(tr);

	tr->stream = rstream;
	tr->line_break = hlGetSystemLineBreak();

	return tr;
}

hlTextReader *hltrCreateFromFile(struct hlFile *file)
{
	hlFileReader *filereader = hlfrCreate(file);
	return_null_if_null(filereader);
	return hltrCreate(&filereader->stream);
}


Bool hltrRelease(hlTextReader *tr)
{
	//**Relesed Source Stream Here !!!
	return_false_if_false(tr->stream->fc->Release(tr->stream));

	return hlmeFree(tr);
}



int hltrReadA(hlTextReader *tr, char *buffer, int size)
{
	return tr->stream->fc->Read(tr->stream, buffer, size);
}


inline char hltrReadCharA(hlTextReader *tr)
{
	return tr->stream->fc->ReadByte(tr->stream);
}


int hltrReadLineA(hlTextReader *tr, char *buffer, int buffer_size)
{
	int i;
	for(i = 0; i < buffer_size - 1; i++)
	{
		int ch = hltrReadCharA(tr);
		if(ch == -1) break;

		if(tr->line_break == et_lbrk_n)
		{
			if(ch == '\n') break;
		}
		else if(tr->line_break == et_lbrk_r)
		{
			if(ch == '\r') break;
		}
		else if(tr->line_break == et_lbrk_rn)
		{
			if(ch == '\r')
			{
				int ch = hltrReadCharA(tr);
				if(ch == -1 || ch == '\n') break;
				//??what does an \r mean?
				buffer[i++] = ch;
			}
		}

		buffer[i] = ch;
	}

	buffer[i] = '\0';
	return i;
}


/*
#include <hl.string.h>
#include <hl.system.memory.buffer.h>


hlStringA *hltrReadStringLineA(hlTextReader *tr)
{
	char buffer[1024];
	struct hlMemoryBuffer mbuffer;
	hlMemoryBuffer_Init(&mbuffer, buffer, 1024);

	while(TRUE)
	{
		int ch = hltrReadCharA(tr);
		if(ch == -1) break;

		if(tr->line_break == et_lbrk_n)
		{
			if(ch == '\n') break;
		}
		else if(tr->line_break == et_lbrk_r)
		{
			if(ch == '\r') break;
		}

		hlMemoryBuffer_AddByte(&mbuffer, (byte)ch);
	}

	hlStringA *str = hlsaNew();
	return_null_if_null(str);
	hlsaCopyCharsInLen(str, mbuffer.space, mbuffer.count);
	hlMemoryBuffer_Release(&mbuffer);
	//...Check result.
	return str;
}
*/

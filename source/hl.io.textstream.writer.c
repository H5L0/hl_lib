#include <hl.io.textstream.h>
#include <hl.system.memory.h>

#include <hl.chars.h>
#include <hl.chars.format.h>

#include <hl.macro.vargs.h>



enum hlTextLineBreak _GetSystemLineBreak()
{
	return et_lbrk_linux;
}


hlTextWriter *hltwCreate(struct hlWriteStream *wstream)
{
	hlTextWriter *tw = hlmeNewType(hlTextWriter);
	return_null_if_null(tw);

	tw->stream = wstream;
	tw->line_break = _GetSystemLineBreak();
	tw->flush_mode = em_tsflush_buffer;

	return tw;
}


hlTextWriter *hltwCreateFromFile(struct hlFile *file)
{
	hlFileWriter *filewriter = hlfwCreate(file);
	return_null_if_null(filewriter);
	return hltwCreate(&filewriter->stream);
}


t_offset hltwSetPointer(hlTextWriter *tw, t_offset offset, enum hlStreamSeekMode mode);


t_offset hltwGetPointer(hlTextWriter *tw)
{
	return tw->stream->fc->GetPointer(tw->stream);
}



int _FindLastLineBreak(const char *chars, int length)
{
	for(int i = 0; i < length; i++)
	{
		if(chars[i] == '\n') return i;
	}
	return -1;
}


int _hltw_write(hlTextWriter *tw, const char *chars, int length)
{
	if(tw->flush_mode == em_tsflush_line)
	{
		int line_break = _FindLastLineBreak(chars, length);
		if(line_break != -1)
		{
			int wn1 = line_break + 1;
			int wn2 = length - wn1;

			wn1 = tw->stream->fc->Write(tw->stream, chars, wn1);
			tw->stream->fc->Flush(tw->stream);

			//Line break is the last character.
			if(wn2 <= 0) return wn1;

			wn2 = tw->stream->fc->Write(tw->stream, chars, wn2);
			return wn1 + wn2;
		}
	}

	//No line break or flush mode is flush while buffer is full.
	return tw->stream->fc->Write(tw->stream, chars, length);
}


int hltwWriteA(hlTextWriter *tw, const char *chars)
{
	int len = hl_chars_length(chars);
	return _hltw_write(tw, chars, len);
}


//hltwFormatWriteA()
int hltwWriteFormatA(hlTextWriter *tw, const char *format, ...)
{
	if(format == NULL || *format == '\0') return 0;

	va_list list;
	va_start(list, format);

	char buffer[4096];
	int count = hlcf_vlist(buffer, buffer + 4096, format, list);
	va_end(list);

	return _hltw_write(tw, buffer, count);
}



int hltwWriteFormatVA(hlTextWriter *tw, const char *format, va_list list)
{
	if(format == NULL || *format == '\0') return 0;

	char buffer[4096];
	int count = hlcf_vlist(buffer, buffer + 4096, format, list);

	return _hltw_write(tw, buffer, count);
}


int hltwWriteLineFormatVA(hlTextWriter *tw, const char *format, va_list list)
{
	if(format == NULL || *format == '\0') return 0;

	char buffer[4096];
	int count = hlcf_vlist(buffer, buffer + 4096, format, list);

	buffer[count == 4096? 4095 : count++] = '\n';

	return _hltw_write(tw, buffer, count);
}



Bool hltwFlush(hlTextWriter *tw)
{
	return tw->stream->fc->Flush(tw->stream);
}


Bool hltwRelease(hlTextWriter *tw)
{
	return_false_if_false(hltwFlush(tw));

	//**Relesed Source Stream Here !!!
	return_false_if_false(tw->stream->fc->Release(tw->stream));

	return hlmeFree(tw);
}
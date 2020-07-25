#include <hl.io.filestream.h>
#include <hl.macro.vargs.h>

//...hl.io.stream.text.h
//...hl.io.text.writer.h
//...hl.io.writer.text.h


//et_xxx : Type
//ef_xxx : Flag
//em_xxx : Mode

enum hlTextLineBreak
{
	et_lbrk_r,
	et_lbrk_n,
	et_lbrk_rn,

	et_lbrk_macos = et_lbrk_r,
	et_lbrk_linux = et_lbrk_n,
	et_lbrk_windows = et_lbrk_rn,
};

enum hlTextLineBreak hlGetSystemLineBreak();


enum hlTextStreamFlushMode
{
	em_tsflush_buffer,
	em_tsflush_line,
};


//-------------------- Text Writer ---------------------//

typedef struct
{
	//hlFileWriter fw;

	struct hlWriteStream *stream;

	enum hlTextLineBreak line_break;

	enum hlTextStreamFlushMode flush_mode;
	
}hlTextWriter;



hlTextWriter *hltwCreate(struct hlWriteStream *wstream);

hlTextWriter *hltwCreateFromFile(struct hlFile *file);

Bool hltwSetFlushMode(hlTextWriter *tw, enum hlTextStreamFlushMode mode);


t_offset hltwSetPointer(hlTextWriter *tw, t_offset offset, enum hlStreamSeekMode mode);

t_offset hltwGetPointer(hlTextWriter *tw);


Bool hltwWriteCharA(hlTextWriter *tw, char ch);

int hltwWriteA(hlTextWriter *tw, const char *chars);

int hltwWriteFormatA(hlTextWriter *tw, const char *format, ...);

int hltwWriteFormatVA(hlTextWriter *tw, const char *format, va_list list);

//...hltwWriteLineA()

//...hltwWriteLineFormatA()

int hltwWriteLineFormatVA(hlTextWriter *tw, const char *format, va_list list);


Bool hltwFlush(hlTextWriter *tw);

Bool hltwRelease(hlTextWriter *tw);



//-------------------- Text Reader ---------------------//

typedef struct
{
	struct hlReadStream *stream;

	enum hlTextLineBreak line_break;
	
}hlTextReader;



hlTextReader *hltrCreate(struct hlReadStream *rstream);

hlTextReader *hltrCreateFromFile(struct hlFile *file);


t_offset hltrSetPointer(hlTextReader *tr, t_offset offset, enum hlStreamSeekMode mode);

t_offset hltrGetPointer(hlTextReader *tr);


char hltrReadCharA(hlTextReader *tr);

int hltrReadA(hlTextReader *tr, char *buffer, int size);

int hltrReadLineA(hlTextReader *tr, char *buffer, int buffer_size);


Bool hltrRelease(hlTextReader *fr);

#include <hl.io.filestream.h>

#include <hl.macro.vargs.h>


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


enum hlTextStreamFlushMode
{
	em_tsflush_buffer,
	em_tsflush_line,
};



typedef struct
{
	//hlFileWriter fw;

	struct hlWriteStream *stream;

	enum hlTextLineBreak line_break;

	enum hlTextStreamFlushMode flush_mode;
	
}hlTextWriter;



hlTextWriter *hltwCreate(struct hlWriteStream *wstream);

hlTextWriter *hltwCreateFromFile(struct hlFile *file);


t_offset hltwSetPointer(hlTextWriter *tw, t_offset offset, enum hlStreamSeekMode mode);

t_offset hltwGetPointer(hlTextWriter *tw);


int hltwWriteA(hlTextWriter *tw, const char *chars);

int hltwWriteFormatA(hlTextWriter *tw, const char *format, ...);

int hltwWriteFormatVA(hlTextWriter *tw, const char *format, va_list list);

//...hltwWriteLineA()

//...hltwWriteLineFormatA()

int hltwWriteLineFormatVA(hlTextWriter *tw, const char *format, va_list list);


Bool hltwFlush(hlTextWriter *tw);

Bool hltwRelease(hlTextWriter *tw);



//------------------- File Reader ---------------------//

typedef struct
{
	struct hlWriteStream *stream;

	enum hlTextLineBreak line_break;
	
}hlTextReader;



hlFileReader *hlfrCreate(struct hlFile *file);

t_size hlfrRead(hlFileReader *stream, void *buffer, t_size size);

t_offset hlfrSetPointer(hlFileReader *fr, t_offset offset, enum hlStreamSeekMode mode);

t_offset hlfrGetPointer(hlFileReader *fr);

Bool hlfrRelease(hlFileReader *fr);



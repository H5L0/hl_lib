#pragma once
#include <hl.type.h>


enum hlStreamSeekMode
{
	e_sseek_start = 0,
	e_sseek_offset = 1,
	e_sseek_end = 2,
};


/*
          Stream
       /          \
StreamWriter  StreamReader
     |              |
 FileWriter     FileReader
     |              |
 TextWriter     TextReader

*/

/*
            Stream
       /             \
  StreamWriter    StreamReader
     |      |         |     |
 FileWriter |    FileReader |
     |      |         |     |
    TextWriter       TextReader

*/


//hlStreamWriter
struct hlWriteStream
{
	t_size (*Write)(struct hlWriteStream *, const void *data, t_size size);
	//t_size (*DirectWrite)(struct hlWriteStream *, void *data, t_size size);

	t_offset (*SetPointer)(struct hlWriteStream *, t_offset, enum hlStreamSeekMode);

	t_offset (*GetPointer)(struct hlWriteStream *);

	Bool (*Flush)(struct hlWriteStream *);

	Bool (*Close)(struct hlWriteStream *);

	//Release;
};


//hlStreamReader
struct hlReadStream
{
	t_size (*Read)(struct hlReadStream *stream, void *buffer, t_size size);

	t_offset (*SetPointer)(struct hlReadStream *, t_offset, enum hlStreamSeekMode);

	t_offset (*GetPointer)(struct hlReadStream *);

	Bool (*Close)(struct hlReadStream *);
};




struct hlTextWriter
{
	struct hlWriteStream stream;
	//hlFileWriter

	t_size (*Write)(struct hlWriteStream *, const char *string);
	t_size (*WriteFormat)(struct hlWriteStream *, const char *format, ...);

	//t_offset (*SetPointer)(struct hlWriteStream *, t_offset, enum hlStreamSeekMode);
	//t_offset (*GetPointer)(struct hlWriteStream *);

	//Bool (*Flush)(struct hlWriteStream *);
	//Bool (*Close)(struct hlWriteStream *);

	//Release;

	u8 newlineSymbol;
};



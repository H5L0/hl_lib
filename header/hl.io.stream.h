#pragma once
#include <hl.type.h>


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


struct hlWriteStream;
struct hlReadStream;


enum hlStreamSeekMode
{
	e_sseek_start = 0,
	e_sseek_offset = 1,
	e_sseek_end = 2,
};



struct hlWriteStreamFC
{
	t_size (*Write)(struct hlWriteStream *, const void *data, t_size size);
	//t_size (*DirectWrite)(struct hlWriteStream *, void *data, t_size size);

	t_offset (*SetPointer)(struct hlWriteStream *, t_offset, enum hlStreamSeekMode);

	t_offset (*GetPointer)(struct hlWriteStream *);

	Bool (*Flush)(struct hlWriteStream *);

	//Bool (*Close)(struct hlWriteStream *);

	Bool (*Release)(struct hlWriteStream *);
};

//hlStreamWriter
struct hlWriteStream
{
	const struct hlWriteStreamFC *fc;
};




struct hlReadStreamFC
{
	t_size (*Read)(struct hlReadStream *stream, void *buffer, t_size size);

	t_offset (*SetPointer)(struct hlReadStream *, t_offset, enum hlStreamSeekMode);

	t_offset (*GetPointer)(struct hlReadStream *);

	//Bool (*Close)(struct hlReadStream *);

	Bool (*Release)(struct hlReadStream *);
};

//hlStreamReader
struct hlReadStream
{
	const struct hlReadStreamFC *fc;
};





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

/* IN USE:
            Stream
       /             \
  StreamWriter  StreamReader
     |                |
 FileWriter      FileReader

  StreamWriter -> FileWriter
      |
  TextWriter

  StreamReader -> FileReader
      |
  TextReader

*/


typedef struct hlWriteStream hlWriteStream;
typedef struct hlReadStream hlReadStream;


enum hlStreamSeekMode
{
	es_seek_Start = 0,
	es_seek_Offset = 1,
	es_seek_End = 2,
};



struct hlWriteStreamFC
{
	t_size (*Write)(struct hlWriteStream *, const void *data, t_size size);

	Bool (*WriteByte)(struct hlWriteStream *, byte);

	//t_size (*DirectWrite)(struct hlWriteStream *, void *data, t_size size);

	t_offset (*SetPointer)(struct hlWriteStream *, t_offset, enum hlStreamSeekMode);

	t_offset (*GetPointer)(struct hlWriteStream *);

	Bool (*Flush)(struct hlWriteStream *);

	//Bool (*Close)(struct hlWriteStream *);

	Bool (*Release)(struct hlWriteStream *);
};


struct hlReadStreamFC
{
	t_size (*Read)(struct hlReadStream *stream, void *buffer, t_size size);

	int (*ReadByte)(struct hlReadStream *);

	t_offset (*SetPointer)(struct hlReadStream *, t_offset, enum hlStreamSeekMode);

	t_offset (*GetPointer)(struct hlReadStream *);

	//Bool (*Close)(struct hlReadStream *);

	Bool (*Release)(struct hlReadStream *);
};



//hlStreamWriter
struct hlWriteStream
{
	const struct hlWriteStreamFC *fc;
};


//hlStreamReader
struct hlReadStream
{
	const struct hlReadStreamFC *fc;
};





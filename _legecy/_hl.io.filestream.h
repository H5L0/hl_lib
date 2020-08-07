#include <hl.io.file.h>
//**分离 file 和 file-io


//
/*FileStream / TextStream / ConsoleStream*/

typedef struct hlFileStream hlFileStream;

struct hlFileStream
{
	hlFile *file;
	char *_buffer;

	t_addr _pointer;

	t_addr _buffer_pos;

	int _buffer_count;

	//int _buffer_capcity;
	//int _buffer_offset;
	//int _offset;

};


struct hlFileStream *hlfsCreate(struct hlFile *);

t_size hlfsRead(struct hlFileStream *fs, void *buffer, t_size size);

t_size hlfsWrite(struct hlFileStream *fs, void *data, t_size size);

//t_size hlfsSetPointer(struct hlFileStream, t_offset, enum hlFileSeekMode);

//设置文件流的指针位置, 绝对地址, 负数offset代表从末尾设定
t_size hlfsSetPointer(struct hlFileStream *, t_offset);

t_size hlfsGotoEnd(struct hlFileStream *);

t_size hlfsMovePointer(struct hlFileStream *, t_offset);

t_size hlfsGetPointer(struct hlFileStream *);

Bool hlfsFlush(struct hlFileStream *);

Bool hlfsClose(struct hlFileStream *);

Bool hlfsRelease(struct hlFileStream *);
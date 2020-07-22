#pragma once
#include <hl.io.file.h>
#include <hl.io.stream.h>




//------------------- File Writer ---------------------//

typedef struct
{
	const struct hlWriteStream *stream;

	hlFile *file;

	char *_buffer;

	t_addr _stream_pos;
	t_addr _buffer_pos;
	int _buffer_capcity;
	//int _buffer_count;
	
}hlFileWriter;



hlFileWriter *hlfwCreate(struct hlFile *file);

t_offset hlfwSetPointer(hlFileWriter *fw, t_offset offset, enum hlStreamSeekMode mode);

t_offset hlfwGetPointer(hlFileWriter *fw);

int hlfwWrite(hlFileWriter *fw, const void *data, int size);

Bool hlfwFlush(hlFileWriter *fw);

Bool hlfwRelease(hlFileWriter *fw);



//------------------- File Reader ---------------------//

typedef struct
{
	const struct hlReadStream *stream;

	hlFile *file;

	char *_buffer;

	t_addr _stream_pos;
	t_addr _buffer_start;
	t_addr _buffer_end;

	int _buffer_capcity;
	//int _buffer_count;
	
}hlFileReader;



hlFileReader *hlfrCreate(struct hlFile *file);

t_size hlfrRead(hlFileReader *stream, void *buffer, t_size size);

t_offset hlfrSetPointer(hlFileReader *fr, t_offset offset, enum hlStreamSeekMode mode);

t_offset hlfrGetPointer(hlFileReader *fr);

Bool hlfrRelease(hlFileReader *fr);




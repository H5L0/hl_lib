#include <hl.io.filestream.h>
#include <hl.system.memory.h>


static const struct hlReadStreamFC _hl_fc_stream_reader = 
{
	(t_size   (*)(struct hlReadStream *, void *, t_size)) hlfrRead,
	(int      (*)(struct hlReadStream *)) hlfrReadByte,
	(t_offset (*)(struct hlReadStream *, t_offset, enum hlStreamSeekMode)) hlfrSetPointer,
	(t_offset (*)(struct hlReadStream *)) hlfrGetPointer,
	(Bool     (*)(struct hlReadStream *)) NULL
};



hlFileReader *hlfrCreate(struct hlFile *file)
{
	//Check file
	//Can Read/Write
	//Direct

	hlFileReader *fr = (hlFileReader*)hlmeNew(sizeof(hlFileReader));
	return_null_if_null(fr);

	fr->stream.fc = &_hl_fc_stream_reader;

	fr->file = file;

	t_size block_size = hlfGetBlockSize(file);
	fr->_buffer = hlmeNew(block_size);
	fr->_buffer_capcity = (int)block_size;

	fr->_buffer_start = 0;
	fr->_buffer_end = 0;

	fr->_stream_pos = 0;
	return fr;
}



//______[###!*******xxxxx]_______  read_buffer
//      ^   ^      ^     ^
// 缓存位置 流位置 缓存结束 文件实际位置

//_____[########xxxxxxx]___!_____  read_raw
//     ^        ^          ^
// 缓存开始    缓存结束    流&文件指针

//_____!______[##########xxxx]___  read_front
//     ^      ^         ^
// 流&文件指针 缓存开始  缓存结束


int _hlfr_read_raw(hlFileReader *fr, void *buffer, int size)
{
	//直接从文件读取剩余部分
	if (size >= fr->_buffer_capcity)
	{
		int rn = hlfRead(fr->file, buffer, size);
		fr->_stream_pos += rn;
		return rn;
	}
	//先从文件读取到缓存区
	else
	{
		int rn = hlfRead(fr->file, fr->_buffer, fr->_buffer_capcity);
		//Read to end.
		if(rn == 0) return 0;

		//*读到文件末尾时, 长度可能不足
		t_size copy_size = rn < size ? rn : size;
		hlmeCopy(fr->_buffer, buffer, copy_size);

		fr->_buffer_start = fr->_stream_pos;
		fr->_buffer_end = fr->_buffer_start + rn;
		fr->_stream_pos += copy_size;
		return copy_size;
	}
}

int _hlfr_read_buffer(hlFileReader *fr, void *buffer, int size)
{
	int bsize = fr->_buffer_end - fr->_stream_pos;
	int offset = fr->_stream_pos - fr->_buffer_start;

	//缓存充足
	if (bsize >= size)
	{
		hlmeCopy(fr->_buffer + offset, buffer, size);
		fr->_stream_pos += size;
		return size;
	}
	//缓存有一部分
	else
	{
		hlmeCopy(fr->_buffer + offset, buffer, bsize);
		fr->_stream_pos += bsize;
		t_size rn = _hlfr_read_raw(fr, buffer + bsize, size - bsize);
		return bsize + rn;
	}
}

int _hlfr_read_front(hlFileReader *fr, void *buffer, int size)
{
	t_size space = fr->_buffer_start - fr->_stream_pos;

	if (space >= size)
	{
		//与缓存区无相交, 直接读无人区
		return _hlfr_read_raw(fr, buffer, size);
	}
	else
	{
		//与缓存区有相交, 先读无相交部分
		int rn = hlfRead(fr->file, buffer, space);
		fr->_stream_pos += rn;

		//..?
		//读取异常, 应该是到文件结尾了
		if (rn != space) return rn;

		t_size n2 = size - space;
		n2 = _hlfr_read_buffer(fr, buffer + space, n2);
		return space + n2;
	}
}


t_size hlfrRead(hlFileReader *fr, void *buffer, t_size size)
{
	if(fr->_stream_pos < fr->_buffer_start)
	{
		return _hlfr_read_front(fr, buffer, size);
	}
	else if(fr->_stream_pos < fr->_buffer_end)
	{
		return _hlfr_read_buffer(fr, buffer, size);
	}
	else 
	{
		return _hlfr_read_raw(fr, buffer, size);
	}
}



int _hlfr_read_raw_byte(hlFileReader *fr)
{
	int rn = hlfRead(fr->file, fr->_buffer, fr->_buffer_capcity);
	//Read to end.
	if(rn == 0) return -1;

	int result = *(fr->_buffer);

	fr->_buffer_start = fr->_stream_pos;
	fr->_buffer_end = fr->_buffer_start + rn;
	fr->_stream_pos ++;
	return result;
}


int hlfrReadByte(hlFileReader *fr)
{
	int offset = fr->_stream_pos - fr->_buffer_start;
	int end = fr->_stream_pos - fr->_buffer_end;
	if(offset >=0 && end < 0)
	{
		fr->_stream_pos++;
		return fr->_buffer[offset];
	}
	else 
	{
		return _hlfr_read_raw_byte(fr);
	}
}



t_offset hlfrSetPointer(hlFileReader *fr, t_offset offset, enum hlStreamSeekMode mode)
{
	t_offset newPos;

	if(mode == e_sseek_start)
	{
		newPos = offset;
	}
	else if(mode == e_sseek_offset)
	{
		newPos = fr->_stream_pos + offset;
	}
	else if(mode == e_sseek_end)
	{
		//**fileSize 不准确
		newPos = hlfGetSize(fr->file) - offset;
	}

	if(newPos < fr->_buffer_start || newPos >= fr->_buffer_end)
	{
		newPos = hlfSeek(fr->file, newPos, e_fseek_start);
	}

	fr->_stream_pos = newPos;
	return newPos;
}



t_offset hlfrGetPointer(hlFileReader *fw)
{
	return fw->_stream_pos;
}



Bool hlfrRelease(hlFileReader *fr)
{
	//return_false_if_false(hlfClose(fr->file));
	return_false_if_false(hlmeFree(fr->_buffer));
	fr->_buffer = NULL;
	return_false_if_false(hlmeFree(fr));
	return TRUE;
}




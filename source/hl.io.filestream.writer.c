#include <hl.io.filestream.h>
#include <hl.system.memory.h>


static const struct hlWriteStream _hl_fc_stream_writer = 
{
	(t_size (*)(struct hlWriteStream *, const void *, t_size)) hlfwWrite,
	(t_offset (*)(struct hlWriteStream *, t_offset, enum hlStreamSeekMode)) hlfwSetPointer,
	(t_offset (*)(struct hlWriteStream *)) hlfwGetPointer,
	(Bool (*)(struct hlWriteStream *)) hlfwFlush,
	NULL
};


hlFileWriter *hlfwCreate(struct hlFile *file)
{
	//Check file
	//Can Read/Write
	//Direct

	hlFileWriter *fs = (hlFileWriter*)hlmeNew(sizeof(hlFileWriter));
	return_null_if_null(fs);

	fs->stream = &_hl_fc_stream_writer;

	fs->file = file;

	t_size block_size = hlfGetBlockSize(file);
	fs->_buffer = hlmeNew(block_size);
	fs->_buffer_capcity = (int)block_size;

	//fs->_buffer_count = 0;
	fs->_buffer_pos = 0;
	fs->_stream_pos = 0;

	return fs;
}



//_____[xxxxxxx!xx]____
//     ^       ^
// 文件实际指针 流指针  

//         ########## <新数据
//_____[xxxxxxxx]___!___
//                  ^
//              文件&流指针


int _hlfw_flush(hlFileWriter *fw)
{
	int wcount = fw->_stream_pos - fw->_buffer_pos;
	wcount = hlfWrite(fw->file, fw->_buffer, wcount);
	fw->_buffer_pos += wcount;
	//??
	return wcount;
}


int _hlfw_write(hlFileWriter *fw, const void *buffer, int size)
{
	/*
	//以最小化内存复制为目标
	if(size > fw->_buffer_capcity)
	{
		_hlfw_flush(fw);
		//直接写入文件
		int wn = hlfWrite(fw->file->id, buffer, size);
		fw->_pointer += wn;
		return wn;
	}
	*/

	int offset = fw->_stream_pos - fw->_buffer_pos;
	int w1 = fw->_buffer_capcity - offset;

	//a.缓存充足
	if (w1 >= size)
	{
		hlmeCopy(buffer, fw->_buffer + offset, size);
		fw->_stream_pos += size;
		return size;
	}
	//b.缓存有一部分
	else
	{
		hlmeCopy(buffer, fw->_buffer + offset, w1);

		//缓存已满, 写入文件
		//int fcount = **
		_hlfw_flush(fw);

		int w2 = size - w1;
		//如果剩余部分较多直接写入文件
		if(w2 >= fw->_buffer_capcity)
		{
			w2 = hlfWrite(fw->file, buffer + w1, w2);
		}
		else
		{
			hlmeCopy(buffer + w1, fw->_buffer, w2);
		}

		fw->_stream_pos += size;
		return size;
	}
}



int hlfwWrite(hlFileWriter *fw, const void *data, int size)
{
	return _hlfw_write(fw, data, size);
}


t_offset hlfwSetPointer(hlFileWriter *fw, t_offset offset, enum hlStreamSeekMode mode)
{
	t_offset newPos = hlfSeek(fw->file, offset, mode);

	//t_addr bstart = fw->_buffer_pos;
	//t_addr bend = bstart + fw->_buffer_capcity;
	
	//_____[#######!__]____
	//_____[####!xxx__]____ < 为了防止之前写入的内容未写入, 只要改变位置都会写缓存.

	if(newPos != fw->_stream_pos)
	{
		_hlfw_flush(fw);
		fw->_buffer_pos = newPos;
		fw->_stream_pos = newPos;
	}

	return newPos;
}


t_offset hlfwGetPointer(hlFileWriter *fw)
{
	return fw->_stream_pos;
}



Bool hlfwFlush(hlFileWriter *fw)
{
	if(fw->_buffer_pos != fw->_stream_pos)
	{
		int fcount = _hlfw_flush(fw);
		return fcount >= 0;
	}
	else return TRUE;
}



Bool hlfwRelease(hlFileWriter *fw)
{
	return_false_if_false(hlfwFlush(fw));
	//hlfClose(fw->file);
	return_false_if_false(hlmeFree(fw->_buffer));
	fw->_buffer = NULL;
	return_false_if_false(hlmeFree(fw));
	return TRUE;
}





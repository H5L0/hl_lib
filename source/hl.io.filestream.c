#include <hl.io.filestream.h>
#include <hl.system.memory.h>

const int _default_buffer_size = (1 << 12);


struct hlFileStream *hlfsCreate(struct hlFile *file)
{
	//Check file
	//Can Read/Write
	//Direct
	struct hlFileStream *fs = hlmeNewType(struct hlFileStream);
	return_null_if_null(fs);
	fs->file = file;
	//Get Page Size
	fs->_buffer = hlmeNew(_default_buffer_size);
	//fs->_buffer_capcity = _default_buffer_size;
	fs->_buffer_count = 0;
	fs->_buffer_pos = 0;
	fs->_pointer = 0;

	return fs;
}

//设置文件流的指针位置, 绝对地址, 负数offset代表从末尾设定
t_addr hlfsSetPointer(struct hlFileStream *fs, t_offset position)
{
	//enum hlFileSeekMode mode = e_fseek_start;
	
	if (position < 0)
	{
		position = hlfSeek(fs->file, -position, e_fseek_end);
		if (position == -1) return -1;

		//仍在缓存内, 需要将文件位置设到缓存末尾
		if (position >= fs->_buffer_pos ||
			position < fs->_buffer_pos + fs->_buffer_count)
		{
			position = hlfSeek(fs->file, fs->_buffer_pos + fs->_buffer_count, e_fseek_start);
			if (position == -1) return -1;
		}
	}
	else if ( position < fs->_buffer_pos ||
		position > fs->_buffer_pos + fs->_buffer_count)
	{
		//在新位置超出缓存时, 需要设定文件位置
		position = hlfSeek(fs->file, position, e_fseek_start);
		if (position == -1) return -1;
	}

	fs->_pointer = position;
	return position;
}

t_addr hlfsGotoEnd(struct hlFileStream *fs)
{
	return 0;
}

t_addr hlfsMovePointer(struct hlFileStream *fs, t_offset offset)
{
	t_addr position = fs->_pointer + offset;
	t_addr bf_end = fs->_buffer_pos + fs->_buffer_count;

	if (position < fs->_buffer_pos || position > bf_end)
	{
		position = hlfSeek(fs->file, bf_end, e_fseek_start);
		if (position == -1) return -1;
	}

	fs->_pointer = position;
	return position;
}



t_size _hlfs_read_raw(struct hlFileStream *fs, void *buffer, t_size size)
{
	//直接从文件读取剩余部分
	if (size >= _default_buffer_size)
	{
		int rn = hlfRead(fs->file, buffer, size);
		fs->_pointer += rn;
		return rn;
	}
	//先从文件读取到缓存区
	else
	{
		int rn = hlfRead(fs->file, fs->_buffer, _default_buffer_size);
		//Read to end.
		if(rn == 0) return 0;

		//*读到文件末尾时, 长度可能不足
		t_size copy_size = rn < size ? rn : size;
		hlmeCopy(fs->_buffer, buffer, copy_size);

		fs->_buffer_pos = fs->_pointer;
		fs->_buffer_count = rn;
		fs->_pointer += copy_size;
		return copy_size;
	}
}

t_size _hlfs_read_behind(struct hlFileStream *fs, void *buffer, t_size size)
{
	t_size offset = fs->_pointer - fs->_buffer_pos;
	t_size bn = fs->_buffer_count - offset;

	//a.缓存充足
	if (bn >= size)
	{
		hlmeCopy(fs->_buffer + offset, buffer, size);
		fs->_pointer += size;
		return size;
	}
	//b.缓存有一部分
	else if (bn > 0)
	{
		hlmeCopy(fs->_buffer + offset, buffer, bn);
		fs->_pointer += bn;
		t_size rn = _hlfs_read_raw(fs, buffer + bn, size - bn);
		return bn + rn;
	}
	//c.缓存无效, 流指针在缓存后
	else
	{
		return _hlfs_read_raw(fs, buffer, size);
	}
}

t_size _hlfs_read_front(struct hlFileStream *fs, void *buffer, t_size size)
{
	t_size space = fs->_buffer_pos - fs->_pointer;

	if (size <= space)
	{
		//与缓存区无相交, 直接读无人区
		return _hlfs_read_raw(fs, buffer, size);
	}
	else
	{
		//与缓存区有相交, 先读无相交部分
		int rn = hlfRead(fs->file, buffer, space);
		fs->_pointer += rn;

		//读取异常, 应该是到文件结尾了
		if (rn != space) return rn;

		t_size n2 = size - space;
		return space + _hlfs_read_behind(fs, buffer + space, n2);
	}
}


t_size hlfsRead(struct hlFileStream *fs, void *buffer, t_size size)
{
	//Check File

	//区分文件指针在缓存区头前/后的情况
	if (fs->_pointer < fs->_buffer_pos)
	{
		return _hlfs_read_front(fs, buffer, size);
	}
	else
	{
		return _hlfs_read_behind(fs, buffer, size);
	}
}

/*
//____[xxx!xxxx]_______
//        ^    ^
//     流指针  文件实际指针

//____[xxxxxxxx]___!___
//                 ^
//             流&文件指针 (bareland)

//流指针超出缓存区
t_size _hlfsReadBareLand(struct hlFileStream *fs, void *buffer, t_size size)
{
	//直接从文件读取剩余部分
	if (size >= _default_buffer_size)
	{
		int rn = hlfRead(fs->file, buffer, size);

		//由于offset在缓存外, 代表文件指针, 只需增加偏移
		fs->_offset += rn;
		return rn;
	}
	//先从文件读取到缓存区
	else
	{
		int rn = hlfRead(fs->file, fs->_buffer, _default_buffer_size);

		//读到文件末尾时, 长度可能不足*
		t_size copy_size = rn < size ? rn : size;
		hlmeCopy(fs->_buffer, buffer, copy_size);

		//将缓存位置指针设为之前offset指示的文件指针
		fs->_buffer_pos += fs->_offset;
		fs->_buffer_count = rn;
		//重设offset到缓存内
		fs->_offset = copy_size;
		return copy_size;
	}
}

//____[xxx!xxxx]_______
//____[xxxxxxxx]___!___
//缓存区头在流指针前
t_size _hlfsReadBehind(struct hlFileStream *fs, void *buffer, t_size size)
{
	t_size bn = fs->_buffer_count - fs->_offset;

	//a.缓存充足
	if (bn >= size)
	{
		hlmeCopy(fs->_buffer + fs->_offset, buffer, size);

		fs->_offset += size;
		return size;
	}
	//b.缓存有一部分
	else if (bn > 0)
	{
		hlmeCopy(fs->_buffer + fs->_offset, buffer, bn);

		fs->_offset = fs->_buffer_count;
		t_size rn = _hlfsReadBareLand(fs, buffer + bn, size - bn);
		return bn + rn;
	}
	//c.缓存无效, 流指针在缓存后
	else
	{
		return _hlfsReadBareLand(fs, buffer, size);
	}
}

//___!__[xxxxxxxx]______
//缓存区在流指针后
t_size _hlfsReadFront(struct hlFileStream *fs, void *buffer, t_size size)
{
	//与缓存区无相交
	if (-fs->_offset > size)
	{
		return _hlfsReadBareLand(fs, buffer, size);
	}
	//与缓存区有相交
	else
	{
		t_size n1 = -fs->_offset;

		int rn = hlfRead(fs->file, buffer, n1);
		fs->_offset += rn;

		//读取异常, 应该是到文件结尾了
		if (rn != n1) return rn;

		t_size n2 = size - n1;
		return n1 + _hlfsReadBehind(fs, buffer + n1, n2);
	}
}


t_size hlfsRead(struct hlFileStream *fs, void *buffer, t_size size)
{
	//Check File
	

	//区分文件指针在缓存区头前/后的情况
	if(fs->_offset < 0)
	{
		return _hlfsReadFront(fs, buffer, size);
	}
	else
	{
		return _hlfsReadBehind(fs, buffer, size);
	}
}
*/




t_size hlfsWrite(struct hlFileStream *fs, void *data, t_size size)
{
	return 0;
}


Bool hlfsFlush(struct hlFileStream *fs)
{
	if(fs->_buffer_count == 0) return TRUE;

	int wcount = hlfWrite(fs->file, fs->_buffer, fs->_buffer_count);

	//if(wcount == -1)
	int gap = fs->_buffer_count - wcount;

	fs->_buffer_count -= wcount;
	fs->_buffer_pos += wcount;
	return gap == 0;
}

//考虑移除这个函数
Bool hlfsClose(struct hlFileStream *fs)
{
	return_false_if_false(hlfsFlush(fs));
	//return_false_if_false(hlfClose(fs->file));
	return hlfClose(fs->file);
}

Bool hlfsRelease(struct hlFileStream *fs)
{
	//...不刷新缓存
	//return_false_if_false(hlfsFlush(fs));
	//...File自行管理
	hlmeFree(fs->_buffer);	//Deal with Error.
	hlmeFree(fs);
	return TRUE;
}

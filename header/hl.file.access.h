#pragma once
#include <hl.type.h>
#include <hl.file.structure.h>


//--------------------- File IO ----------------------//

enum hlFileSeekMode
{
	ef_seek_Start  = 0,  //eFileSeekMode_Start
	ef_seek_Offset = 1,
	ef_seek_End    = 2,
	ef_seek_Data = -1,
	ef_seek_Hole = -1,

	//efSeekStart
};

//失败返回-1
t_offset hlfSeek(struct hlFile *file, t_offset offset, enum hlFileSeekMode mode);


//...block/count
int hlfRead(struct hlFile *file, void *buffer, int length);

int hlfWrite(struct hlFile *file, const void *data, int length);


Bool hlfSync(struct hlFile *file);


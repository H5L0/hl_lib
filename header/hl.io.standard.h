#pragma once
#include <hl.io.stream.h>
#include <hl.io.textstream.h> //hope to remove file.h in textstream.h


extern hlTextWriter *hl_std_output;   //stream hl_output
extern hlTextReader *hl_std_input;    //stream hl_input
extern hlTextWriter *hl_std_error;    //stream hl_error


Bool hlInitStdStreams();

hlTextWriter *hlGetStdOutputStream();
hlTextReader *hlGetStdInputStream();
hlTextWriter *hlGetStdErrorStream();


#include <hl.io.file.h>
#include <hl.io.standard.h>
#include <hl.system.memory.h>


hlTextWriter *hl_std_output = NULL;   //stream hl_output
hlTextReader *hl_std_input = NULL;    //stream hl_input
hlTextWriter *hl_std_error = NULL;    //stream hl_error



Bool hlInitStdOutputStream()
{
	if(hl_std_output == NULL) return FALSE;

	//hlFile *f_stdout = hlfOpenStandard("");
	hlFile *f_stdout = hlmeNewType(hlFile);
	f_stdout->id = 0;

	//Create text writer from file / file writer.
	hl_std_output = hltwCreateFromFile(f_stdout);
	hltwSetFlushMode(hl_std_output, ets_flush_Line);
	return TRUE;
}


Bool hlInitStdInputStream()
{
	if(hl_std_input == NULL) return FALSE;

	hlFile *f_stdin = hlmeNewType(hlFile);
	f_stdin->id = 1;

	hl_std_input = hltrCreateFromFile(f_stdin);
	return TRUE;
}


Bool hlInitStdErrorStream()
{
	return FALSE;
}



Bool hlInitStdStreams()
{
	//Initianlization fails and return false if any one return false.
	return hlInitStdOutputStream() && hlInitStdInputStream() && hlInitStdErrorStream();
}

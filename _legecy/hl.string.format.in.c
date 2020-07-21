#include <hl.string.format.in.h>

//#Rename to hl.string.foramt.vargs.c

//#include <hl.macro.vargs.h>


enum e_arg_type
{
	et_arg_i,
	et_arg_ui,
	et_arg_l,
	et_arg_ul,
	et_arg_t,	//st
	et_arg_ut,	//t
	et_arg_x,
	et_arg_p,
	et_arg_e,
	et_arg_f,
	et_arg_ff,
	et_arg_s
};


//hl_string_format_vtype
int format_vtype_to_string(
	const char *fstart,
	const char *f_end,
	char *buffer,
	char *b_end,
	void *parg, enum e_arg_type type)
{
	switch(type)
	{
		case et_arg_i:  return strf_s32(buffer, b_end, fstart, f_end, *(s32*)parg);
		case et_arg_ui: return strf_u32(buffer, b_end, fstart, f_end, *(u32*)parg);
		default: return 0;
	}
}



const int _args_temp_size = 32;

int parse_types(const char *pstype, u8 args_type[_args_temp_size])
{
	if(pstype == NULL) return 0;

	int argc = 0;
	bool uflag = FALSE;
	bool confirmed = FALSE;
	char ch;
	while((ch = *pstype) != '\0')
	{
		if(ch == ',')
		{
			if(confirmed)
			{
				if(argc == _args_temp_size - 1)
				{
					return _args_temp_size + 1; //代表参数数量超出帧数组
				}

				++argc;
				confirmed = FALSE;
				uflag = FALSE;
			}
		}
		else
		{
			if(confirmed) continue;

			switch(ch)
			{
				case 'u':
				{
					uflag = TRUE;
					break;
				}
				case 'i':
				{
					if(uflag) args_type[argc] = et_arg_ui;
					else args_type[argc] = et_arg_i;
					confirmed = TRUE;
					break;
				}
				case 'l':
				{
					if(uflag) args_type[argc] = et_arg_ul;
					else args_type[argc] = et_arg_l;
					confirmed = TRUE;
					break;
				}
				//case ' ': continue;
			}
		}
		
		++pstype;
	}

	if(confirmed) ++argc;

	return argc;
}



static inline bool _CharIsNumber(char ch) { return ch >= '0' && ch <= '9'; }

//istart != iend.
int parse_index(const char *istart, const char *iend)
{
	int value = 0;
	//# Compare between istart and iend could be post last.
	for(int ch = *istart; istart != iend; ch = *(++istart))
	{
		if(_CharIsNumber(ch))
		{
			value = value * 10 + (ch - '0');
		}
		else return -1;
	}
	return value;
}



//buffer != NULL, len(buffer) > 0.
//format != NULL, len(format) > 0.
//types  /= NULL.
//int hl_string_format_vargs(
int strf_vargs(
	char *buffer,
	char *buffer_end,
	const char *format, const char *types, void** args_list)
{
	u8 args_type[_args_temp_size];

	int argc = parse_types(types, args_type);
	if(argc > _args_temp_size); //warning: too much args.


	//int len = hlGetCharsLength(format);
	//if(len == 0) return 0;
	//const char *format_end = format + len + 1;

	const char *pformat = format;
	char *pbuffer = buffer;

	const char *tstart = NULL;  //start of one arg format.
	bool lastIsEscape = FALSE;
	bool haveSeparator = FALSE;
	int index = -1;
	
	do{
		char ch = *pformat;

		//Format ended.
		if(ch == '\0') break;

		//If tstart is null, format search has not started.
		if(tstart == NULL)
		{
			//use '{ to escape from new format search.
			if(ch == '\'')
			{
				lastIsEscape = TRUE;
			}
			else if (ch == '{')
			{
				if(lastIsEscape) *(pbuffer++) = '{';
				//>> Format search start <<
				else tstart = pformat + 1;
			}
			else
			{
				*(pbuffer++) = ch;
				lastIsEscape = FALSE;
			}
		}
		else
		{
			//<<End of format search>>
			//# Removed check of '\0', So the last format will be thrown away.
			if (ch == '}')
			{
				//If format has no ':' separator, it is index number.
				if(!haveSeparator)
				{
					index = parse_index(tstart, pformat);
					tstart = pformat;
				}

				//Invalid index. just print a char '?'.
				if(index < 0 || index >= argc) 
				{
					*(pbuffer++) = '?';
				}
				//Format stage.
				else
				{
					enum e_arg_type type = args_type[index];
					void *parg = &args_list[index];

					//No format string. use default format.
					if(tstart == pformat)
					{
						tstart = NULL;
					}

					int count = format_vtype_to_string(tstart, pformat, pbuffer, buffer_end, parg, type);
					pbuffer += count;
				}

				//Clean tstart to indicate searching has ended.
				tstart = NULL;
				haveSeparator = FALSE;
			}
			else if(ch == ':')
			{
				//A format str like {:__--} have no valid number.
				//Add 1 to index by default. 
				if(tstart == pformat) ++index;
				else index = parse_index(tstart, pformat);

				tstart = pformat + 1;
				haveSeparator = TRUE;
			}
		}

		++pformat;
	}while(pbuffer != buffer_end); //Buffer exhausted.

	return (int)(pbuffer - buffer);
}
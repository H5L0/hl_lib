#include <hl.chars.format.h>
#include <hl.macro.vargs.h>

enum e_arg_type
{
	et_arg_invalid,
	et_arg_i,   //int (s32)
	et_arg_ui,
	et_arg_l,   //long long (s64)
	et_arg_ul,
	et_arg_t,   // siged register type: st
	et_arg_ut,  //unsiged register type: t
	et_arg_x,
	et_arg_p,
	et_arg_e,
	et_arg_f,
	et_arg_ff,  //double: d df fl
	et_arg_s
};


int hlcf_type(
	const char *fstart,
	const char *f_end,
	char *buffer,
	char *b_end,
	const void *parg, enum e_arg_type type)
{
	switch(type)
	{
		case et_arg_i:  return hlcf_s32(buffer, b_end, fstart, f_end, *(s32*)parg);
		case et_arg_ui: return hlcf_u32(buffer, b_end, fstart, f_end, *(u32*)parg);
		case et_arg_ul: return hlcf_u64(buffer, b_end, fstart, f_end, *(u64*)parg);
		case et_arg_s:  return hlcf_str(buffer, b_end, fstart, f_end, *(const char **)parg);
		case et_arg_x:
		case et_arg_p:  return hlcf_ptr(buffer, b_end, fstart, f_end, *(void **)parg);
		default: return 0;
	}
}


enum e_arg_type parse_arg_type_strict(const char *tstart, const char *tend)
{
	if(tstart >= tend) return et_arg_invalid;
	//Remove leading space.
	while(*tstart == ' ')
		if(++tstart == tend)
			return et_arg_invalid;
	//Remove trailing space.
	while(*(tend-1) == ' ')
		if(tstart == --tend)
			return et_arg_invalid;

	//Type str should like: "ui".
	if(tend - tstart > 2)
		return et_arg_invalid;

	char c1 = *tstart;
	//2 char length type str must start with 'u'/'f'
	if(tend - tstart == 2)
	{
		char c2 = *(tstart + 1);
		if(c1 == 'u')
		{
			if(c2 =='i') return et_arg_ui;
			if(c2 =='l') return et_arg_ul;
			if(c2 =='t') return et_arg_ut;
			else return et_arg_invalid;
		}
		if(c1 == 'f')
		{
			if(c2 == 'f') return et_arg_ff;
			else return et_arg_invalid;
		}
		return et_arg_invalid;
	}
	else
	{
		switch(c1)
		{
			case 'i': return et_arg_i;
			case 'l': return et_arg_l;
			case 't': return et_arg_t;
			case 'x': return et_arg_x;
			case 'p': return et_arg_p;
			case 'e': return et_arg_e;
			case 's': return et_arg_s;
			case 'f': return et_arg_f;
			default: return et_arg_invalid;
		}
	}
	return et_arg_invalid; //unreachable.
}


enum e_arg_type parse_arg_type(const char *tstart, const char *tend)
{
	if(tstart == tend) return et_arg_invalid;
	bool uflag = FALSE;
	do
	{
		switch(*tstart)
		{
			case 'u': uflag = TRUE; break;
			case 'i': return uflag ? et_arg_ui : et_arg_i;
			case 'l': return uflag ? et_arg_ul : et_arg_l;
			case 't': return uflag ? et_arg_ut : et_arg_t;
			case 'x': return et_arg_x;
			case 'p': return et_arg_p;
			case 'e': return et_arg_e;
			case 's': return et_arg_s;
			case 'f': return et_arg_f;
			//case ' ': break;
			//default: return et_arg_invalid;
		}
	}while(++tstart != tend);
	return et_arg_invalid;
}



void *va_get_next_ptr(va_list vl)
{
	if(vl->gp_offset != 48)
	{
		void *p = vl->reg_save_area + vl->gp_offset;
		vl->gp_offset += 8;
		return p;
	}
	else
	{
		void *p = vl->overflow_arg_area;
		vl->overflow_arg_area += 8;
		return p;
	}
}



//format: "{s} is {i:--__}"
//buffer != NULL, len(buffer) > 0.
//format != NULL, len(format) > 0.
int hlcf_vlist(char *buffer, char *buffer_end, const char *format, va_list args_list)
{
	const char *pformat = format;
	char *pbuffer = buffer;

	const char *tstart = NULL;  //start of one arg format.
	const char *sp_end = NULL;  //next char pos of ':' separator.
	
	do{
		char ch = *pformat;

		//Format ended.
		if(ch == '\0') break;

		//If tstart is null, the format search has not started.
		if(tstart == NULL)
		{
			//use ' before { to escape from new format search.
			if(ch == '\'')
			{
				ch = *(pformat + 1);
				if(ch == '\0') break;
				if(ch == '{') ++pformat;
				else ch = '\'';
				
				*(pbuffer++) = ch;
			}
			//>> Format search start <<
			else if (ch == '{')
			{
				tstart = pformat + 1;
			}
			else
			{
				*(pbuffer++) = ch;
			}
		}
		else
		{
			if(ch == ':')
			{
				if(sp_end == NULL) sp_end = pformat;
			}
			//<<End of format search>>
			//# Removed check of '\0', So the last format will be thrown away.
			else if (ch == '}')
			{
				void *parg = va_get_next_ptr(args_list);
				
				//if format has no ':' separator, end in pformat.
				enum e_arg_type atype = parse_arg_type_strict(tstart, sp_end ? sp_end : pformat);

				//Invalid type. just print a char '?'.
				if(atype == et_arg_invalid) 
				{
					*(pbuffer++) = '?';
				}
				//Format stage.
				else
				{
					//No format string. use default format.
					if(tstart == pformat || sp_end == NULL) tstart = NULL;
					else tstart = sp_end + 1;

					int count = hlcf_type(tstart, pformat, pbuffer, buffer_end, parg, atype);
					pbuffer += count;
				}

				//Clean tstart to indicate searching has ended.
				tstart = NULL;
				sp_end = NULL;
			}
		}

		++pformat;
	}while(pbuffer != buffer_end); //Buffer exhausted.

	return (int)(pbuffer - buffer);
}





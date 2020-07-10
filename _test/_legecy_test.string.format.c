

int _strf_u32(const char *format, char *buffer, u32 bSize, u32 value)
{
	char raws[12];
	char *praw = raws;
	/*
	u64 bcd = (u64)value + (value/10) * 6;
	printf("0x%X\n", (u32)bcd);
	//0+
	do {
		*(praw++) = (char)(bcd & 0x0F) + '0';
		bcd  >>= 4;
	} while(bcd != 0);*/

	do {
		u32 n = value % 10;
		value = value / 10;
		*(praw++) = n + '0';
	} while(value != 0);


	bool align_left = FALSE;
	//bool negetive = FALSE;
	char *pbuf = buffer;
	char c;

	if(format != NULL)
	{
		if(*format=='|')
		{
			align_left = TRUE;
			format++;
		}
		if(*format!='\0')
		{
			if(align_left)
			{
				do {
					c = *(format++);
					//整数左对齐时不应该填0
					if(c=='-')      *(pbuf++) = praw == raws ? '0' : *(--praw);
					else if(c=='_') *(pbuf++) = praw == raws ? ' ' : *(--praw);
					else if(c=='*') while(praw != raws) *(pbuf++) = *(--praw);
					else if(c=='?')	*(pbuf++) = '+';  //改为替换符号位
					else if(c=='!') *(pbuf++) = '+';
					else if(c=='|') continue;
					else *(pbuf++) = c;

				} while(c != '\0');
				*pbuf = '\0';	
				return (int)(pbuf - buffer);
			}
			else
			{
				char *nraw = raws;
				const char *pfm = format;
				while(*pfm!='\0') pfm++;
				do {
					c = *(--pfm);
					if(c=='-')      *(pbuf++) = praw == nraw ? '0' : *(nraw++);
					else if(c=='_') *(pbuf++) = praw == nraw ? ' ' : *(nraw++);
					/*if(c=='-'||c=='_')
					{
						if(value == 0)
						{
							*(pbuf++) = c == '-' ? '0' : '_';
						}
						else
						{
							u32 n = value % 10;
							value = value / 10;
							*(pbuf++) = n + '0';
						}
					}*/
					else if(c=='*') while(praw != nraw) *(pbuf++) = *(nraw++);
					else if(c=='?') *(pbuf++) = '+';
					else if(c=='|') continue;
					else *(pbuf++) = c;

				} while(pfm != format);

				*pbuf = '\0';
				int scount = (int)(pbuf - buffer);
				//调换方向
				while(pbuf > buffer) 
				{
					--pbuf;
					c = *pbuf; *pbuf = *buffer; *buffer = c;
					++buffer;
				}
				return scount;
			}
		}
	}

	//直接填充数字
	while(praw != raws) *(pbuf++) = *(--praw);
	*pbuf = '\0';
	return (int)(pbuf - buffer);
}



int strf_string(const char *format, char *buffer, u32 bSize, const char *str)
{

	bool align_left = FALSE;
	//bool negetive = FALSE;
	char *pbuf = buffer;
	char c;

	if(format != NULL)
	{
		if(*format=='|')
		{
			align_left = TRUE;
			format++;
		}
		if(*format!='\0')
		{
			if(align_left)
			{
				do {
					c = *(format++);
					if(c=='-'||c=='_')
					{
						*(pbuf++) = *str=='\0' ? ' ' : *(str++);
					}
					else if(c=='*')
					{
						while(str!='\0') *(pbuf++) = *(str++);
					}
					else if(c=='|') continue;
					else *(pbuf++) = c;

				} while(c != '\0');
				*pbuf = '\0';	
				return (int)(pbuf - buffer);
			}
			
		}
	}

	return 0;
}
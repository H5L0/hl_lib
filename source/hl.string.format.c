//#include <hl.string.format.h>




char *U32ToString(const char *format, u32 value)
{
	"xxxx";

	char raws[12];

	int rcount = 0;
	do//while(value!=0)
	{
		u32 n = value % 10;	//* use mod(x,*n)
		value = value / 10;
		raws[i] = n + '0';
		rcount++;
	}while(value != 0);

	//count all chars.
	int scount = 0;
	bool align_left = FALSE;
	const char *pc = format;
	for(char c = *pc; c!='\0'; c = *(++pc))
	{
		if(c=='-') ++scount;	//数字位
		else if(c=='0') ++scount;	//0
		else if(c=='_') ++scount;	//可空数字位
		else if(c=='?') ++scount;	//固定符号位
		else if(c=='&') ++scount;	//替换符号位
		else if(c=='*') scount+=rcount;	//全值符
		else if(c=='|')
		{
			if(scount==0)
			{
				align_left = TRUE;
			}
		}
	}

	int flen = (int)(pc - format);
	printf("flen:%d\n", flen);
	if(flen == 0)
	{
		//format至少有一个字符
		format = "*";
		pc = format+1;
	}
	char *str = malloc(scount+1);
	str[scount] = '\0';

	int si = 0;
	int ri = 0;

	if(align_left)
	{
		ri = rcount;		
		do {
			char c = *format;
			if(c=='*')
			{
				while(ri!=-1)
				{
					str[si++] = raws[--ri];
				}
			}
			else
			{
				if(c=='-')
				{
					c = ri==-1?'0':raws[--ri];
				}
				else if(c=='_') //可空位
				{
					c = ri==-1?' ':raws[--ri];
				}
				else if(c=='|') continue;
				else if(c=='?') continue;
				
				str[si++] = c;
			}		
		}while((++format) != pc)
	}
	else
	{
		pc = format;
		si = scount;
		for(int i = flen-1; i!= -1; --i)
		{
			char c = *(format+i);

			if(c=='*')
			{
				while(ri!=rcount)
				{
					str[--si] = raws[ri++];
				}
			}
			else
			{
				if(c=='-')
				{
					c = ri==rcount?'0':raws[ri++];
				}
				else if(c=='_') //可空位
				{
					c = ri==rcount?' ':raws[ri++];
				}
				else if(c=='|') continue;
				else if(c=='?') continue;
				
				str[--si] = c;
			}		
		}
	}

	return str;
}

char *S32ToString(const char *format, s32 value);

char *U64ToString(const char *format, u64 value);

char *S64ToString(const char *format, s64 value);

char *HexToString(ureg value);

char *FloatToString(float value);

char *DoubleToString(double value);







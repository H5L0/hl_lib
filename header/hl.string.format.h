#include <hl.type.h>

char *U32ToString(const char *format, u32 value);

char *S32ToString(const char *format, s32 value);

char *U64ToString(const char *format, u64 value);

char *S64ToString(const char *format, s64 value);

//char *PointerToString(t_addr value);
char *HexToString(ureg value);

char *FloatToString(float value);

char *DoubleToString(double value);




char * hlsFormat(const char format, ...)
{
	//默认右对齐，左空格
	"   8", "[i:4]"
	"   8", "[i:#4]"

	"8---", "[i:4#-]"
	"---8", "[i:-#4]"

	"-  8", "[i:4._]"
	"-008", "[i:4.=]"
	"-008", "[i:4.0]"
	"-008", "[i:4.]"	//4.0 / 4.

	"  -8", "[i,4]"
	"-008", "[i,4=0]"	//+ 显示所有位
	"00-8", "[i:0#4]"	//前面填充0

	"0123",
	"0100", "[i:.1]"	//保留1位有效数字
	"0100", "[i:.-2]"	//不计算后2位


	"  -0.1", "[f:6.1]"
	"-000.1", "[f:6=0.1]"
	"-   .1", "[f:6=_.1]"
	"-  0.1", "[f:6=_0.1]"

	"- 00.12","[f:?=nnxx.xx]"
	"-   .12","[f:?=nnnn.xx]"

	//"  -0.12","{f:nnnnnx.xx}"	<< -0.1234f

	"236.12","{f:x.xx}"	<< 236.1234f
	"236.12","{f:<x.xx|}"	<< 236.1234f
	"6.1234","{f:|x.xx>}"	<< 236.1234f
	//整数部分默认全部表示，小数部分默认只表示给出的位数

	"{s<red/white=high>:?=__--.--}"
	"{s<0xff00ff/white=high>:?=__--.--}"
	"{s<0d909/0d181=high>:?=__--.--}"


	"{s12}"		//    xxxxxxxx|
	"{|s12}"	//xxxxxxxx    |

	"{f:|?__-.--}"	//[f:6=_.2]
	"{s:|_32}"

	//x 数字位 一定有数字（可能是0）
	//a 可空数字位 数字或空格  a/n
	//z 数字0
	//f 浮点数数字位
	//s 字符位
	//? 符号位 一定有符号+/-
	//?=x 符号替换位 ﹣/原来的位	?/signed/c
	//| 对齐符 只能放在最左或最右？
	//* 全值符 整个内容


	"{xxzz}"	//0100|		z!=0
	"{?=xxxx}"	//-008|
	"{xxxx}"	//00-8|
	"{aaaa}"	//  -8|
	"{|*}"		//-8|
	"{|cxxx}"	//-8  |

	"00-8", "[i:x4]"
	"-008", "[i,?=x4]"

	//ff
	//xx
	//ss


	"%i(0.8)[0], word_float:%f[3]value{}"

	"(%f,0.8_)[0]"

	"[f,0.8][0]"

	"[f][0](#0.8)"

	"[f:0,0.3_]"

	"[f:#0.3].1"

	"[f<1:#8.3]", "[f]", "[fl:.3]"

	"i u/ui l ul f fl"
	"t ut"	//sreg, ureg
	"e g"
	"p h"	//pointer, hex
	"bool"	//bool

}

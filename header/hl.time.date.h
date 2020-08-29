#pragma once
#include <hl.type.h>


struct hlDate
{
	u16 year;       // A.D. 0-65535
	u8 month;       // 12M
	u8 day;         // 28-31D
	u8 hour;        // 24h
	u8 minute;      // 60m
	u8 second;      // 60s
	u8 centisecond; // 1/100s
};

/*
struct hlDateNS
{
	u16 year;  //A.D. 0-65535 (s16?)
	u8 month;  //12M
	u8 day;	   //28-31D
	u8 hour;   //24h
	u8 minute; //60m
	u8 second; //60s
	u8 __pd;
	u32 ns;    //10^-9s
};
*/

#if 0
struct hlDate _hl_time64_to_date(u64 time64)
{
	struct hlDate date;
	time64 /= 10000000;
	date.centisecond = (u8)(time64 % 100);
	time64 /= 100;
	date.second = (u8)(time64 % 60);
	time64 /= 60;
	date.minute = (u8)(time64 % 60);
	u32 time32 = (u32)(time64 / 60);
	date.hour = time32 % 24;
	time32 /= 24;
	//date.day = time32 %

	return date;
}
#endif
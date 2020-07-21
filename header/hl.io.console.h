#pragma once
#include <hl.type.h>
//#include <hl.io.keyboard.h>	//还是不引入为好


int hlcsWriteVA(const char *format, const char *type, void **args);

//char *hlcsReadLineNA();


int hlcsWriteA(const char *format, ...);

int hlcsWriteLineA(const char *format, ...);


bool hlcsRead(char *buffer, int length);

int hlcsReadLineA(char *buffer, int bsize);


typedef enum hlKeyCode hlKeyCode;

enum hlKeyCode hlcsReadKey();


int hlcsReadChar();

int hlcsReadInt();

float hlcsReadFloat();



bool hlcsTryReadChar(char *pchar);

bool hlcsTryReadInt(char *pint);

float hlcsTryReadFloat(char *pfloat);





//{i:|?__-.--}
//{i<1:|?__-.--}
//{f:|?__-.--}
//{s:|?__-.--}



//{|?__-.--}
//{0:|?__-.--}
//{2:|?__-.--}

//"f,s,i,u,ul,ff"

//hlWriteLineA("The '{} of '{} is: '{3:?__-.--}", "s,s,i", str1, str2, v1);
//hlWriteLineA("The {1} of {} is: {3:?__-.--}", "s,s,i", str1, str2, v1);
//hlWriteLineA("The [1] of [] is: [3]{?__-.--}", "s,s,i", str1, str2, v1);
//hlWriteLineA("The @1 of @ is: @3{?__-.--}, 123@@mail.com", "s,s,i", str1, str2, v1);






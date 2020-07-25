#pragma once
#include <hl.type.h>
//#include <hl.io.keyboard.h>	//还是不引入为好


Bool hlcsInit();
Bool hlcsRelease();


int hlcsWriteA(const char *format, ...);

int hlcsWriteLineA(const char *format, ...);


int hlcsReadA(char *buffer, int size);

int hlcsReadLineA(char *buffer, int buffer_size);


int hlcsReadChar();

typedef enum hlKeyCode hlKeyCode;

enum hlKeyCode hlcsReadKey();


int hlcsReadInt();

float hlcsReadFloat();


Bool hlcsTryReadChar(char *pchar);

Bool hlcsTryReadInt(char *pint);

float hlcsTryReadFloat(char *pfloat);




//int hlcsWriteVA(const char *format, const char *type, void **args);

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






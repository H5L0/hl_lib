#pragma once
#include <hl.type.h>
#include <hl.io.keyboard.h>	//还是不引入为好



int hlcsWriteA(const char *format, ...);


int hlcsWriteLineA(const char *format, ...);


char *hlcsReadLineA();

enum hlKeyCode hlcsReadKey();


int hlcsReadChar();

int hlcsReadInt();

float hlcsReadFloat();



bool hlcsTryReadChar(char *pchar);

bool hlcsTryReadInt(char *pint);

float hlcsTryReadFloat(char *pfloat);










#pragma once
#include <hl.type.h>


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


Bool hlcsSetSize(int w, int h);

Bool hlcsGetSize(int *pw, int *ph);


Bool hlcsSetPointer(int x, int y);

Bool hlcsMovePointer(int x, int y);


//Bool hlcsDrawScreen()





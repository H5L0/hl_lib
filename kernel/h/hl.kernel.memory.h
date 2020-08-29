#pragma once
#include <hl.type.h>


extern char _edata;
extern char __bss_start;
extern char _end;


#define _DATA_END_  ((void*)&_edata)
#define _BSS_START_ ((void*)&__bss_start)
#define _BSS_END_   ((void*)&_end)


void hl_memory_init();

void *hl_memory_alloc(t_size size);

bool hl_memory_resize(void *space, t_size size);

bool hl_memory_free(void *space);



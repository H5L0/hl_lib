
#include <stdio.h>
#include <unistd.h>
#include <hl.kernel.memory.h>
#include <hl.linux.syscall.h>

int my_static_value = 0x1234;
int my_static_bss_value;

int hlStart()
{
	my_static_bss_value = 0x5678;

	//printf("_start:\t%p\n", _start);
	printf("_edata:      %p\n", _DATA_END_);
	printf("__bss_start: %p\n", _BSS_START_);
	printf("_end:        %p\n", _BSS_END_);

	printf("--------------------------\n");
	printf("Heap Start: %p\n", sbrk(0));
	printf("--------------------------\n");

	hl_memory_init();

	void *p1 = hl_memory_alloc(32);
	void *p2 = hl_memory_alloc(128);

	printf("p1:%p\np2:%p\n", p1, p2);

	bool r1 = hl_memory_free(p1);
	//bool r2 = hl_memory_free(p2);
	bool r2 = 0;

	printf("r1:%i\nr2:%i\n", r1, r2);

	void *p3 = hl_memory_alloc(32);
	void *p4 = hl_memory_alloc(128);

	printf("p3:%p\np4:%p\n", p3, p4);

	bool r3 = hl_memory_free(p3);
	bool r4 = hl_memory_free(p4);

	printf("r3:%i\nr4:%i\n", r3, r4);

	printf("\033[1;35mColor\033[0m \033[1;33mPrint\033[0m \033[1;31mTest\033[0m\n");
	//printf("<red:Color> <blue:Test>\n");
	//printf("<0d900:Color> <0d009:Test>\n"); //x*28

	sys_write(1, "System Call Write Test!\n", 25);

	char buffer[32];
	int ic = sys_read(0, buffer, 32);
	sys_write(0, buffer, ic);

	/*
	for(u32 *ptr = (u32*)_DATA_END_; ptr != (u32*)_BSS_END_; ptr++)
	{
		printf("%p: %X\n", ptr, *ptr);
	}

	for(u32 *ptr = (u32*)_heap_start; ptr != (u32*)result; ptr++)
	{
		ureg addr = (ureg)ptr & ((1<<12)-1);
		printf("%p (%.4x): %x\n", ptr, addr, *ptr);
	}
	*/

	return 0;
}

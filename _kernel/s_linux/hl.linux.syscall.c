


//12 设定新的堆结束地址
void *sys_brk(void *addr_end)
{
	void *brk_number = (void*)12;
	__asm__ __volatile__ (
		"movq %0, %%rax\n\t"  //调用号 存入rax寄存器
		"movq %1, %%rdi\n\t"  //第一个参数 存入rdi寄存器
	 	"syscall"
		:
		:"m"(brk_number), "m"(addr_end)
		:"rax", "rdi"
	);
	return (void*)brk_number;
}









//X64-86架构 系统调用 AT&T汇编代码
//全部采用x64_fastcall
//函数输入参数：rdi, rsi, rdx, rcx, r8, r9
//系统调用参数：rdi, rsi, rdx, r10, r8, r9
//rcx、r11会被破坏

.text

.global sys_read
//n000
//[eax] ([edi]fd, [rsi]buffer, [edx]count)
sys_read:
	movq $0, %rax
	syscall
	ret

.global sys_write
//n001
//[rax] ([rdi]addr)
sys_write:
	movq $1, %rax
	syscall
	ret

.global sys_open
//n002
//[eax] ([edi]fd, [rsi]access, [edx]flags)
sys_open:
	movq $2, %rax
	syscall
	ret

.global sys_close
//n003
//[rax] ([rdi]fd)
sys_close:
	movq $3, %rax
	syscall
	ret

.global sys_stat
//[rax] ([rdi]addr)
sys_stat:
	movq $4, %rax
	syscall
	ret

.global sys_fstat
//[rax] ([rdi]fd, [rsi]pstat)
sys_fstat:
	movq $5, %rax
	syscall
	ret

.global sys_seek
//[eax] ([edi]fd, [rsi]offset, [edx]mode)
sys_seek:
	movq $8, %rax
	syscall
	ret



.global sys_mmap
//n009
//[rax] ([rdi]addr, [rsi]length, [rdx]prot, [rcx]flags, [r8]fd, [r9]offset)
sys_mmap:
	push %r10
	movq $9, %rax
	movq %rcx, %r10
	syscall
	pop %r10
	ret


//n012 
//[rax] ([rdi]addr)
.global sys_brk
sys_brk:
	movq $12, %rax
	syscall
	ret


//n060
.global sys_exit
sys_exit:
	movq $60, %rax
	syscall
	ret










SECTION .text

global fika_sysv_syscall


fika_sysv_syscall:

	; This shifts the registers so that we comply with the SysV calling convention.
	mov rax, rdi
	mov rdi, rsi
	mov rsi, rdx
	mov rdx, rcx
	syscall
	ret
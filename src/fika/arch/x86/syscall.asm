
SECTION .text

fika_syscall:
	mov	eax, [esp+4]  ; syscall-no (4)
	mov	ebx, [esp+8]  ; file-no (1)
	mov	ecx, [esp+12] ; msg
    mov	edx, [esp+16] ; len
	int	0x80
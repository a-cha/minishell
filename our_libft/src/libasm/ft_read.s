; args order: rdi, rsi, rdx, rcx
; ssize_t	read(int fildes, void *buf, size_t nbyte);

extern ___error

section		.text
global		_ft_read

_ft_read:
	mov		rax, 0x2000003
	syscall
	jc		error
	ret

error:
	push	rax
	call	___error
	pop		qword [rax]
	mov		rax, -1
	ret

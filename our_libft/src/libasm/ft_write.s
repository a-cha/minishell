; args order: rdi, rsi, rdx, rcx
; ssize_t	ft_write(int fildes, const void *buf, size_t nbyte);

extern ___error

section		.text
global		_ft_write

_ft_write:
	mov		rax, 0x2000004
	syscall
	jc		error
	ret

error:
	push	rax
	call	___error
	pop		qword [rax]
	mov		rax, -1
	ret

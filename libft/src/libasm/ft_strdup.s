; args order: rdi, rsi, rdx, rcx
; char	*strdup(const char *s1);

extern _malloc
extern _ft_strlen
extern _ft_strcpy

section		.text
global		_ft_strdup

_ft_strdup:
	call	_ft_strlen
	inc		rax
	push	rdi
	mov		rdi, rax
	call	_malloc
	test	rax, rax
	jz		error
	pop		rdi
	push	rsi
	mov		rsi, rdi
	mov		rdi, rax
	call	_ft_strcpy
	pop		rsi
	ret

error:
	pop		rdi
	ret

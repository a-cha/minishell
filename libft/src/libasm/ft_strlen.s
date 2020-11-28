; args order: rdi, rsi, rdx, rcx
; size_t	ft_strlen(char const *str);

section		.text
global		_ft_strlen

_ft_strlen:
	mov		rax, -1

loop:
	inc		rax
	cmp		byte [rdi + rax], 0
	jnz		loop
	ret

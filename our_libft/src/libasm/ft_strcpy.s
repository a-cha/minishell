; args order: rdi, rsi, rdx, rcx
; char	*ft_strcpy(char * dst, const char * src);

section		.text
global		_ft_strcpy

_ft_strcpy:
	mov		rcx, -1

loop:
	inc		rcx
	mov		dl, byte [rsi + rcx]
	mov		byte [rdi + rcx], dl
	test	dl, dl
	jnz		loop
	mov		rax, rdi
	ret

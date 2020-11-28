; args order: rdi, rsi, rdx, rcx
; int	ft_strcmp(const char *s1, const char *s2);

section		.text
global		_ft_strcmp

_ft_strcmp:
	mov		rcx, -1
	mov		rax, 0
	mov		rdx, 0

loop:
	inc		rcx
	cmp		byte [rdi + rcx], 0
	je		return
	mov		al, byte [rdi + rcx]
	cmp		al, byte [rsi + rcx]
	je		loop

return:
	mov		al, byte [rdi + rcx]
	mov		dl, byte [rsi + rcx]
	sub		rax, rdx
	ret

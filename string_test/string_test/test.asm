

.code
string_reverse_X64 proc
	push rsi
        push rdi
        push rbx
	mov rax, 0
	mov rdi, 0
	cmp rdx, 2
	jl exit
	sub rdx, 2
	mov rsi, rdx
	string_round:
		string_reverse:
			mov bl, byte ptr[rcx + rdi]
			mov bh, byte ptr[rcx + rdx]
			mov byte ptr[rcx + rdi], bh
			mov byte ptr[rcx + rdx], bl
			dec rdx
			inc rdi
			cmp rdi, rdx
		jl string_reverse
	mov rdi, rax
		string_find_whitespace:
			mov bl, byte ptr[rcx + rdi]
			cmp bl, 20h
			je find_space
			inc rdi
			cmp rdi, rsi
		jl string_find_whitespace
		ja exit
		inc rdi
	find_space:
	lea rdx, [rdi - 1]
	mov rdi, rax
	lea rax, [rdx + 2]
	jmp string_round
	exit:
        pop rbx
        pop rdi
        pop rsi
	ret
string_reverse_X64 endp
END

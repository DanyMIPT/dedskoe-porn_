section .data

	buf db "%d  %s sanya go buhat'  %o %b %x %b %% %c", 0
	tmp times 256 db 0

	num_len	equ 10
	num: times num_len db 0

	new_line db "mipt", 10
	t equ $-new_line

section .text
	global _start

_start:
	;mov rax, 25
	;mov rbx, 2

	;call to_sys
	;call printf_line

	;mov cl, 48
	;call printf_symbol

	;mov r9, new_line
	;call printf_str

	push 49
	push 25
	push 1024
	push 225
	push 10
	push new_line
	push 256

	mov r8, buf
	call pars
	
	add rsp, 56

	call end

;=========================
;parser
;Input: stack full of shit, r8 - line  to parse
;Destroy:
;============================
pars:
	push rbp
	mov rbp, rsp

	mov rcx, r8; pointer after %
	mov rdx, r8; pointer before %
	mov r15, 16
while:
	cmp byte [r8], 0

	jne continue


	call printf_text

	pop rbp
	ret

continue:
	cmp byte [r8], 37    ; % == 37
	jne skip
	call printf

skip:
	mov rdx, r8
	inc r8
	jmp while

;===================================
;switch what to do if %
;==================================
printf:
	inc r8
	call printf_text

	cmp byte [r8], 111 ; 111 = o
	jne skip_o
	call pr_o
	jmp end_p
skip_o:

	cmp byte [r8], 120 ; 120 == x
	jne skip_x
	call pr_x
	jmp end_p

skip_x:

	cmp byte [r8], 98 ; 98 == b
	jne skip_b
	call pr_b
	jmp end_p

skip_b:
	cmp byte [r8], 100 ; 100 == d
	jne skip_d
	call pr_d
	jmp end_p

skip_d:
	cmp byte [r8], 99 ; 99 == c
	jne skip_c
	call pr_c
	jmp end_p

skip_c:
	cmp byte [r8], 115 ; 115 == s
	jne skip_s
	call pr_s
	jmp end_p

skip_s:
	cmp byte[r8], 37 ; 37 == %
	jne end_p
	call pr_pr
	sub r15, 8

end_p:
	mov rdx, r8
	mov rcx, r8

	add r15, 8
	ret

pr_pr:
	mov al, 37
	call printf_symbol

	ret

pr_s:
	mov r9, [rbp + r15]
	call printf_str

	ret

pr_c:
	mov al, [rbp + r15]
	call printf_symbol

	ret


pr_digit:
	mov rax, [rbp + r15]

	push rcx
	call to_sys
	call printf_line
	pop rcx

	ret

pr_o:
	mov rbx, 8
	call pr_digit

	ret

pr_x:
	mov rbx, 16
	call pr_digit

	ret

pr_b:
	mov rbx, 2
	call pr_digit

	ret

pr_d:
	mov rbx, 10
	call pr_digit

	ret
;=======================
;printf text
;Input: ecx - char*, edx - length
;Destruct: eax, ebx
;=======================

printf_text:
	cmp rdx, 0
	je exit_

	push rax
	push rbx
	push rcx
	push rdx


	mov eax, 4
	mov ebx, 1

	sub rdx, rcx
	add rcx, 1

	int 80h

	mov rdx, r8
	mov rcx, r8

	pop rdx
	pop rcx
	pop rbx
	pop rax

exit_:
	ret

;=========================
;strlen
;Input: edi - const char*
;Output: edx - string length
;Destroy: edi, ecx
;===========================
strlen:
	cld

	xor ecx, ecx
	dec ecx
	xor eax, eax

	repne	scasb

	not ecx
	dec edx
	mov edx, ecx

	ret

;================================
;Printf line
;Input: r9 - char*
;Destroy eax, ebx, edx, rcx
;================================

printf_str:
	push rax
	push rbx
	push rcx
	push rdx

	mov rdi, r9
	call strlen

	cmp edx, 0
	je exit

	mov eax, 4
	mov ebx, 1
	mov rcx, r9

	int 80h

exit:
	pop rdx 
	pop rcx
	pop rbx
	pop rax

	ret

;=====================
;printf a symbol
;Input: r11 - symbol
;Destroy: rax, rbx, rdx, rcx
;====================

printf_symbol:
	push rax
	push rbx
	push rcx
	push rdx

	mov byte [num], al

	mov eax, 4
	mov ebx, 1

	mov rcx, r11
	mov ecx, num
	mov edx, 1

	int 80h

	pop rdx
	pop rcx
	pop rbx
	pop rax

	ret

;==========================
;Printf digit line
;Input: num - digit line
;       num_len - line length
;       rcx     - number of digits
;Destroy: eax, ebx, rcx, edx, r9
;=====================

printf_line:
	push rax
	push rbx
	push rdx

	mov eax, 4
        mov ebx, 1
        mov rdx, rcx
	inc rdx

        neg rcx
        add ecx, num + num_len - 1

        int 80h

	pop rdx
	pop rbx
	pop rax

	ret

;========================
;Transform digit in rbx system
;Input: rax - number, rbx - sys_num
;Output: num, rcx
;Destroy: rsi, rdx, rcx, rax
;======================

to_sys:
	push rax
	push rbx
	push rdx
	push rsi

	mov rsi, num + num_len - 1
	xor rcx, rcx
	;mov rdx, rax
	;xor rax, rax

	mov r13, rbx
loop:
	xor rdx, rdx
	idiv r13
	mov byte [esi], dl

	cmp byte [esi], 9
	jna small

	add byte [esi], 55
	jmp big

small:
	add byte [esi], 48

big:
	dec esi

	inc rcx
	cmp eax, 0
	jne loop

	dec rcx

	pop rsi
	pop rdx
	pop rbx
	pop rax
	ret

;==========================
;Ends programm
;=========================

end:
	mov eax, 1
	mov ebx, 0
	int 80h

	ret

.model tiny
.code
org 100h

Start:
T
		mov di, offset Text

		call strlen
		mov ah, 02h
		mov dx, di
		int 21h

		mov ax, 4c00h
		int 21h 

;==============================================================================
; Counts number of characters in the string
; Entry: DI - adress of string
; Del:   AX, BX
; RET:   DI - length of the string
;===============================================================================

strlen		proc

		mov bx, di
		mov al, 00
		repnz scasb

		sub di, bx
		ret

		endp	

end Start

;================================================================================
; Entry: SI - pointer to the string, DI - place to copy
; Ret:	 DI - copied string
;===============================================================================

strcpy		proc

while:		
		cmp [si], 0
		je out

		movsb
		jmp while
				
out:		
		ret
		endp	

;====================================================================================
; Entry: SI - string, al - symbol
; Ret:   DI - string
;=================================================================================

strchar		proc

find_char:
		cmp byte ptr ds:[di], 00h
		je no_char

		scasb
		jne find_char

end_proc:
		dec di
		ret
		endp

no_char:
		mov di, 1
		jmp end_proc

;===================================================================================
; Entry: SI - string, al - symbol
; Ret:   BX - string
;===================================================================================

strrchar	proc
		xor bx, bx

find_last_char:
		cmp ds:[di], 0
		je end_strr

		scasb
		jne no_write_di

		mov bx, di

no_write_di:

		jmp find_last_char

end_strr:
		ret
		endp
		
;====================================================================================
		
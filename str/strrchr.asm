.model tiny
.code
org 100h

Start:
Text:		db 'zdr', '$'
		mov si, offset Text
		call strrchar

		mov ax, 4c00h
		int 21h

;===================================================================================
; Entry:  SI - string, al - symbol
; Ret:    BX - string
; Delete: BX
;===================================================================================

strrchar	proc
		xor bx, bx

find_last_char:
		cmp byte ptr ds:[di], 00h
		je end_strr

		scasb
		jne no_write_di

		mov bx, di

no_write_di:

		jmp find_last_char

end_strr:
		ret
		endp
		

end Start
		 

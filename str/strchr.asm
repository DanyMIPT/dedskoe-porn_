.model tiny
.code
org 100h

Start:
Text:		db 'zdr', '$'
		mov si, offset Text 
		mov ax, 4c00h
		int 21h 

;====================================================================================
; Entry:  ds:SI - string, al - symbol
; Ret:    DI - string
; Delete: -
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

end Start

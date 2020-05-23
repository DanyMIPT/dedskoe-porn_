.model tiny
.code
org 100h

Start:
Text:		db 'zdr', '$'
		call strlen

		mov ax, 4c00h
		int 21h 

;==============================================================================
; Counts number of characters in the string
; Entry: DI - adress of string
; Del:   AX, BX, CX
; RET:   DI - length of the string
;===============================================================================

strlen		proc
		
		cld
		
		xor cx, cx
		dec cx

		mov bx, di
		mov al, 00
		repnz scasb

		sub di, bx
		ret

		endp	

end Start

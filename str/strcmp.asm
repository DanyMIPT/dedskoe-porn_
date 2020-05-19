.model tiny
.code
org	100h

start:
	mov	ax, 4C00h
	int	21h

;======================================================================================================
; Inputs:	ES:DI - address of first string
;		DS:SI - address of second string
; Outputs:	FLAGS - result of CMP of first null byte in one string and
;		corresponding char in second string
; Destructs:	DI, SI
;==================================================================================================
strcmp	proc
		cld
loop_start:
		cmpsb
		jne	end_loop

		cmp	byte ptr es:[di - 1], 00h
		je	null_di

		cmp	byte ptr ds:[si - 1], 00h
		je	null_si

		jmp	loop_start

null_di:
		cmp	byte ptr ds:[si - 1], 00h
		ret

null_si:
		cmp	00h, byte ptr es[di - 1]
		ret

end_loop:
	ret

strcmp	endp

end	start

.model	tiny
.code
org 100h

Start:
	call	memchr

	mov	ax, 4C00h
	int	21h
;==============================================================================================
; Inputs: 	DS:DI - memory address
;		CX - length
;		AL - byte to find
; Outputs:	DI - adress of first equal byte 
;		or DI + CX if there is no such byte
; Destructs:	DI, CX, AL, ES
;===================================================================================================
memchr		proc

		cld	

		repne 	scasb

		jne	end_mem
		dec	di

end_mem:	ret
memchr	endp

end Start

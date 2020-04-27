.model	tiny
.code
org	100h

start:

	mov	ax, 4C00h
	int	21h

end	start

;=============================================================================================
; Inputs:	ES:DI - adress of data
;		AL - byte to put
;		CX - length
; Outputs:	Nothing
; Destructs:	CX, DI
;==================================================================================================

memset	proc

	cld
	rep	stosb

	ret

memset	endp
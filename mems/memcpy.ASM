.model	tiny
.code
org	100h

start:

	mov	ax, 4C00h
	int	21h

;=================================================================================================
; Inputs:	DS:SI - source address
;		ES:DI - destination address
;		CX - length
; Outputs:	Nothing
; Destructs:	DI, SI, CX, AX
;=======================================================================================================

memcpy	proc

	cld
	rep	movsb

	ret

memcpy	endp

end	start
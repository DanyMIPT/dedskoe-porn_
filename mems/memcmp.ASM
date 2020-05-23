.model	tiny
.code
org	100h

start:
	mov	ax, 4C00h
	int	21h

;====================================================================================================
; Inputs:	DI - first address
;		SI - second address
;		CX - length
; Outputs:	FLAGS - result of CMP first unequal bytes
; Destructs:	DI, SI, CX, ES, AX
;=================================================================================================

memcmp	proc

	mov	ax, ds
	mov	es, ax

	cld
	repe	cmpsb
	ret
memcmp	endp

end start

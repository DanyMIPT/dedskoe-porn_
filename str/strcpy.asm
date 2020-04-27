.model tiny
.code
org 100h

locals $$

Start:
		mov ax, 4c00h
		int 21h 

;================================================================================
; Entry: DS:SI - pointer to the string, ES:DI - place to copy
; Ret:	 DI - copied string
;===============================================================================

strcpy		proc

while:		
		cmp byte ptr es:[si], 00h
		je out

		movsb
		jmp while
				
out:		
		ret
		endp	


end Start
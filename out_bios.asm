.model tiny
.code
org 100h

Start:
		mov ah, 0eh
		mov al, 'H'
		int 10h

		mov ah, 0ah
		mov al, '!'
		mov cx, 5d
		int 10h
 
		mov ax, 4c00h
		int 21h

end		Start		
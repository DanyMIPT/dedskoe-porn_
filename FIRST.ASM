.model tiny
.code
org 100h

Start:          
		mov ah, 09h
		mov dx, offset Message
      	        int OUTPUT	  
		
		mov ax, 4c00h
		int OUTPUT


OUTPUT		equ 21h
Message: 	db 'Smth', '$'


end		Start
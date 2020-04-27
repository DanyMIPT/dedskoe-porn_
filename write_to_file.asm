.model tiny
.data
 .code
org 100h

public EndLabel
public open_file
public pointer_to_end
public close_file
public write_file

;====================================================
;Destroy - ax, bx
;Output  - bx - file handler, dx - file trail
;===================================================
OPEN		equ	3dh

FILE_NAME: db "S:\log\loger.log", 0 

open_file	proc
		
		mov dx, offset FILE_NAME
		mov ah, OPEN
		mov al, 1
		int 21h

		mov bx, ax	
		ret
endp

;==================================================
;Input - bx - file handler
;Destroy - ax, cx, dx
;=====================================================
MOVE_POINTER	equ	42h

pointer_to_end	proc

		mov ah, MOVE_POINTER   
		mov cx, 0
		mov dx, 0	
		mov al, 2
		int 21h

		ret
endp

;==================================================
;Input - bx - file handler
;	 cx - number of bytes to write
;	 ds:dx - adress of a buffer
;Destroy - ah
;====================================================
WRITE		equ 	40h


write_file	proc

		
		mov ah, WRITE
		int 21h

	        ret
endp

;==================================================
;Input - bx - filg handler
;Destroy - ah
;===================================================
CLOSE		equ	3eh

close_file	proc
		
		mov ah, CLOSE
		int 21h

		ret
endp

EndLabel:
End

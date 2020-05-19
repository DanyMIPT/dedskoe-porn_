.model tiny
.286
.386
.code
org 100h

extrn EndLabel
extrn frame: proc
extrn wait_

OUTPUT 		    equ 21h
OUTPUT_CODE_AX      equ 4C00h
FRAME_COLOUR 	    equ 07F7eh
SYMBOLS_ONE_LINE    equ 80
VIDEO_MEMORY	    equ 0b800h
LINES  		    equ 5
WIDTH		    equ 60
LEFT_CORNER_X	    equ 18	
LEFT_CORNER_Y       equ 15


INT_9		equ 9*4

Start:
		call interupt_new 
				
		call stay_resident

;--------------------------------------
New09		proc
		
		push ax bx es dx di

		in al, 60h
		mov bl, al    
		call shine_bit

		cmp bl, 2
		jne skip
		call frame_
		
		stosw
skip:         
		mov al, 20h 	; say that interrupt ended		
		out 20h, al

		pop di dx es bx ax

		db 0eah
Old09 		dw 0
		dw 0

		iret
		endp


;===============================================
;Calls frame and safe registers
;Input - al - scan code
;=============================================

frame_		proc

		mov ax, VIDEO_MEMORY
		mov es, ax

		mov al, dl
		mov di, ((LEFT_CORNER_X + LINES / 2) * 80 + LEFT_CORNER_Y + WIDTH / 2) * 2
		mov ah, 4eh
		stosw

		push ax es cx bx dx di

		mov ax, VIDEO_MEMORY
		mov es, ax
		
		mov cx, FRAME_COLOUR		
		mov bl, LINES
		mov bh, WIDTH
		mov dl, LEFT_CORNER_X
		mov dh, LEFT_CORNER_Y

		call frame

		pop di dx bx cx es ax

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
;Output - Old09 - adress of old interupt 
;==============================================
interupt_new	proc

		xor ax, ax
		mov es, ax

		cli
		mov bx, INT_9

		mov ax, word ptr es:[bx]
		mov Old09, ax
		mov ax, word ptr es:[bx+2]
		mov Old09 + 2, ax

		mov word ptr es:[bx], offset New09
		mov ax, cs
		mov word ptr es:[bx+2], ax
		sti

		ret
endp

;============================================
;Programm ends and stay resident
;============================================

RESIDENT	equ	3100h

stay_resident	proc

		mov ax, RESIDENT
		mov dx, offset EndLabel 
		shr dx, 4
		inc dx  
		inc dx
		int 21h
		ret
endp
	 
End

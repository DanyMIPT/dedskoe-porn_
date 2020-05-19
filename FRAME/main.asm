.model tiny
.code
org 100h

public frame_text
extrn EndLabel
extrn frame: proc

OUTPUT 		    equ 21h
OUTPUT_CODE_AX      equ 4C00h
FRAME_COLOUR 	    equ 0FF7eh
SYMBOLS_ONE_LINE    equ 80
VIDEO_MEMORY	    equ 0b800h
LINES  		    equ 15
WIDTH		    equ 60
LEFT_CORNER_X	    equ 7	
LEFT_CORNER_Y       equ 15

frame_text	proc
		mov ax, VIDEO_MEMORY
		mov es, ax
		
		mov cx, FRAME_COLOUR		
		mov bl, LINES
		mov bh, WIDTH
		mov dl, LEFT_CORNER_X
		mov dh, LEFT_CORNER_Y

		call frame
	
		mov ax, VIDEO_MEMORY
		mov es, ax

		mov ax, 80d
		mov bx, 11d
		imul bx
		
		mov cx, 20d
		mov dx, 0
		
		call count_bx
loop_start:	

		mov byte ptr es:[bx], dl
		inc bx
		inc cx
		mov byte ptr es:[bx], 4eh 
		inc bx
		
		cmp dx, 0FFh
		je local_1

		cmp cx, 60d
		je change_str	

		jmp skip

change_str:	mov cx, 20d
		add ax, 80d
		call count_bx

skip:
		inc dl		
		inc cx	
		loop loop_start

count_bx:
		mov bx, ax
		add bx, cx
		push ax
		mov ax, 2d
		push dx
		imul bx
		mov bx, ax
		pop dx
		pop ax
ret

local_1:
endp
end		 

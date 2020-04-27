.model tiny

double = 2

.code
org 100h

Start:
		mov ax, 0b800h
		mov es, ax

		mov ax, 80d
		mov dx, 6d
		mul dx
		mov dx, 10d
		add ax, dx
		mov cx, 2
		mul cx
		mov bx, ax

		mov ax, 80d
		mov dx, 18d
		mul dx
		mov dx, 10d
		add ax, dx
		mov cx, 2
		mul cx
		mov di, ax

		mov cx, 60 
loop_str:
		mov byte ptr es:[bx], 2
		inc bx
		mov byte ptr es:[bx], 62h
		inc bx

		mov byte ptr es:[di], 2
		inc di
		mov byte ptr es:[di], 62h
		inc di
loop loop_str
		
		mov ax, 80d
		mov dx, 7d
		mul dx
		mov dx, ax

		mov cx, 10d
 
loop_wall:
		mov ax, dx
		add ax, cx
		mov bx, 2
		push dx
		mul bx
		mov bx, ax
		pop dx

		mov byte ptr es:[bx], 2
		inc bx
		mov byte ptr es:[bx], 62h

		mov ax, dx
		add ax, cx
		add ax, 59
		mov di, 2
		push dx
		mul di
		pop dx
		mov di, ax

		mov byte ptr es:[di], 2
		inc di
		mov byte ptr es:[di], 62h
			
		add dx, 80
		inc cx
		
		cmp dx, 19d * 80d
		je out_loop 
loop loop_wall	
	
out_loop:
		mov ax, 4C00h
		int 21h

end Start
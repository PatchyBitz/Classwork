org 100h
	global _start
	section .text
		_start:

			call menu
				
		exit:
			mov ax, 4c00h
			int 21h

takeDisk: ; takeDisk(target) , returns val in ax
	push bp
	push bx
	mov bp, sp
	mov bx, [ bp + 6 ] ; Address of the tower before return address, bp, and bx
	mov al, [bx] ; Index
	cmp al, 0 ; Test al, al 
	jnz .disk; If not less than 0, jump to .disk
	jz exit  ; If zero, nothing was there
	.disk:
		mov ah, al
		dec ah
		mov [bx], ah ; Decrease the disk size
		add bl, al ; Move to the disk
		mov al, [bx] ; Disk
		mov ah, '#'
		mov [bx], ah ; Clear the disk
		xor ah, ah ; Disk is now in ax
	.end:

	pop bx
	pop bp
ret

putDisk: ; putDisk(hand,Target)
	push bp ;2
	push bx ;2 
	mov bp, sp
	mov bx, [bp + 8 ] ; target
	mov al,[bx] ;size of tower
	mov dl,[bp+6] ;Hand
	add bl,al
	mov dh,[bx]
	sub dh,48
	sub dl,48
	cmp dl,dh
	ja exit
	.disk:
		sub bl,al
		mov ah, al
		inc ah
		mov [bx],ah
		add bl, ah
		mov al,[bp + 6]
		xor ah,ah
		mov [bx],al
	.end:

	pop bx
	pop bp
	; body
ret

ret
menu:
	pusha
	mov cl, 0
	.repeat: 
		mov ah,9	
		mov dx, newline + 1
		int 21h
		push txt
		push right_t	 + 1
		push center_t	 + 1
		push left_t	   + 1 ; From right to left
		call printT ;prinT(txt,right_t,center_t,left_t)
		add sp, 8 ; 4 x 2B
			

		; push left_t
		; call takeDisk 
		; add sp, 2
		; push ax ;Pushes return from disk for future assignments

		; push txt   ; Testing code to see if I can pick up and set straight back down.
		; push right_t	 + 1
		; push center_t	 + 1
		; push left_t	   + 1 ; From right to left
		; call printT
		; add sp, 8 ; 4 x 2B
		
		; ;mov dl,al
		; ;mov ah, 2
		; ;int 21h
		
		; pop ax
		; push right_t
		; push ax
		; call putDisk
		; add sp,4

		; ; push left_t
		; ; push ax
		; ; call putDisk

		; push txt
		; push right_t	 + 1
		; push center_t	 + 1
		; push left_t	   + 1 ; From right to left
		; call printT
		; add sp, 8 ; 4 x 2B


	mov ah,1
	int 21h
	cmp al,'1'
	je .left_t
	cmp al,'2'
	je .mid_t
	cmp al,'3'
	je .right_t
	jmp .end
		;jmp .pull


	.left_t:
		push left_t
		cmp cl,0
		jz .pull
		jnz .put
		

	.mid_t:
		push center_t
		cmp cl,0
		jz .pull
		jnz .put
		

	.right_t:
		push right_t
		cmp cl,0
		jz .pull
		jnz .put
		

	.pull:
		call takeDisk
		mov [hand+1],ax
		add cl,1
		add sp,2
		jmp .repeat
		
	.put:
		xor ah,ah
		mov ax,[hand+1]
		push ax
		call putDisk
		sub cl,1
		add sp,4
		jmp .repeat

	.end:
	
	popa
ret


printT: ; print(leftt,centt,rightt,Text)
	; three towers and txt
	push bp

	mov bp, sp
	mov ah, 9
	mov dx, [ bp + 4 ] ; Left tower
	int 21h
	mov dx, [ bp + 6 ] ; Center tower
	int 21h
	mov dx, [ bp + 8 ] ; Right tower
	int 21h
	mov dx, [ bp + 10 ] ; Text
	int 21h

	pop bp
ret
	
section .data
	newline 	db 0, 10,13,36
	left_t		db 3, '3', '2', '1', 10, 13, 36
	center_t	db 0, '#', '#', '#', 10, 13, 36
	right_t		db 0, '#', '#', '#', 10, 13, 36
	txt			db "1 - L, 2 - C, 3 - R", 10, 13, 36
	hand 		db 1,"4"
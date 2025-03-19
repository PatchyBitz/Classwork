org 100h
	global _start
	section .text
		_start:

			call menu
				
		exit:
			mov ax, 4c00h
			int 21h

takeDisk:
	push bp
	push bx
	mov bp, sp
	mov bx, [ bp + 6 ] ; Address of the tower before return address, bp, and bx
	mov al, [bx] ; Index
	cmp al, 0 ; Test al, al 
	jnz .disk; If not less than 0, jump to .disk
	jz .end  ; If zero, nothing was there
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

putDisk:
	; body

ret
menu:
	pusha
	.repeat:
		push txt
		push right_t	 + 1
		push center_t	 + 1
		push left_t	   + 1 ; From right to left
		call printT
		add sp, 8 ; 4 x 2B
			
		;mov ah, 1
		;int 21h


		push left_t
		call takeDisk
		add sp, 2

		push txt
		push right_t	 + 1
		push center_t	 + 1
		push left_t	   + 1 ; From right to left
		call printT
		add sp, 8 ; 4 x 2B

	.end:
	
	popa
ret


printT:
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
	left_t		db 3, '3', '2', '1', 10, 13, 36
	center_t	db 0, '#', '#', '#', 10, 13, 36
	right_t		db 0, '#', '#', '#', 10, 13, 36
	txt			db "1 - L, 2 - C, 3 - R", 10, 13, 36
;Student: YenShae Fan
;CSCI 361 Spring 2025
;Assignment: Class14 - Procedures, Logical Operations Calculator
;Professor Jakub Pach

;I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced. 
;Any collaboration or use of external resources has been ;properly cited. I am fully aware of the consequences of academic 
;dishonesty and agree to abide by the university's academic integrity policy. I understand the importance the consequences of plagiarism.



org 100h
	global _start
	section .text
		_start:
				mov cx, 8
				mov dx, buffer
				call readN
				
				mov cx, 8
				mov dx, sebuff
				call readN

				mov dx,buffer
				call printN
				call newLine

				mov dx, sebuff
				call printN
				call newLine

				mov bx,buffer
				mov bp,sebuff
				call Ands
				mov dx,ax
				call printN

				call newLine
				
				mov bx,buffer
				mov bp,sebuff
				call ors
				mov dx,ax
				call printN
				call newLine

				; call XORS
				; mov dx,answ
				; call printN

				; call newLine

				; call NOTa
				; mov dx,answ
				; call printN

				; call newLine

				; call NOTb
				; mov dx,answ
				; call printN
				; call newLine
				
				; call NAND
				; mov dx,answ
				; call printN
				;  call newLine
			
				;  call NOR
				;  mov dx,answ
				;  call printN
				;  call newLine

				;  call XNOR
				;  mov dx,answ
				;  call printN



				_end:
				mov ax, 4c00h
				int 21h


		Ands:
		xor di, di 
				.ands1: ;Return section head for loop
					mov ax,answ
					cmp di, cx	
					je .end1 	
					mov dl, [bx + di] ; Uses dl and dh due to each character only being one byte
					sub dl, "0"
					mov dh,[bp + di]
					sub dh, "0"
					and dl,dh
					add dl, "0"
					mov [ answ + di],dl ; Stores each character received from the operation - Expect to be used with PrintN
					inc di
					jmp .ands1
				.end1:
					ret

		ors:
			xor di, di 
			.ors1:
				mov ax,answ
				cmp di, cx
				je .end1 
				mov dl,[bx + di] 
				mov dh,[bp + di]
				or dl,dh
				mov [answ + di],dl
				inc di
				jmp .ors1
			.end1:
		ret

		XORS:
		xor di, di 
				.xors1:
				cmp di, cx
				je .end1
				mov dl,[bx + di]
				sub dl,48 
				mov dh,[bp + di]
				sub dh,48
				xor dl,dh
				add dl,48
				mov [ answ + di],dl
				inc di
				jmp .xors1
				.end1:
					ret
	
		NOTa:
		xor di, di 
				.nota1:
				cmp di, cx
				je .end1 
				mov dl,[bx + di]
				sub dl,48
				xor dl,1 			;Effectively NOT operation due to actual NOT running against the entire register
				add dl,48
				mov [answ + di],dl
				inc di
				jmp .nota1
				 .end1:
				 	ret

		NOTb:
		xor di, di 
				.notb1:
				cmp di, cx
				je .end1 
				mov dl,[bp + di] 
				sub dl,48
				xor dl,1
				add dl,48
				mov [ answ + di],dl
				inc di
				jmp .notb1
				.end1:
					ret
		
		NAND:
		xor di, di 
				.NAND1:
				cmp di, cx
				je .end1 
				mov dl,[buffer + di] 
				mov dh,[sebuff + di]
				sub dl,48
				sub dh,48;
				and dl,dh
				xor dl,1
				add dl,48
				mov [ answ + di],dl
				inc di
				jmp .NAND1
				.end1:
					ret
		
		NOR:
		xor di, di 
				.NOR1:
				cmp di, cx
				je .end1 
				mov dl,[buffer + di] 
				mov dh,[sebuff + di]
				sub dl,48
				sub dh,48
				or dl,dh
				xor dl,1
				add dl,48
				mov [ answ + di], dl
				inc di
				jmp .NOR1
				.end1:
					ret

		XNOR:
			xor di, di 
				.XNOR1:
				cmp di, cx
				je .end1 
				mov dl,[buffer + di] 
				mov dh,[sebuff + di]
				sub dl,48
				sub dh,48

				mov bl,dl ;Takes copy of dx registers and uses bx as the "Not" path 
				mov bh,dh
				xor bh,1  ;XOR by 1 to negate.
				xor bl,1


				and bl,bh
				and dl,dh

				or dl,bl

				add dl,48
				mov [ answ + di],dl
				inc di
				jmp .XNOR1
				.end1:
					ret

		








		readN:
		; 'doctype'
		; cx contains the number of characters to read
		; dx contains the address where the data will be stored
			xor di, di		; DI is used as the destination index
			mov bx, dx		; Copy of the destination address
			mov ah, 1

			.loop1:			; Local label instead of a global one
				cmp di, cx	; Check condition
				je .end1 	; like di < cx
				int 21h 	; Read key into AL
				mov [bx + di], al
				inc di
				jmp .loop1
			.end1:
		ret

		printN:
		; 'doctype'
		; cx contains the number of characters to print
		; dx contains the address where the data is stored
			xor si, si		; SI is used as the source index
			mov bx, dx		; Copy of the source address
			mov ah, 2
			.loop1:			; Local label instead of a global one
				cmp si, cx	; Check condition
				je .end1	; like di < cx
				mov dl, [bx + si]
				int 21h 	; Print character
				inc si
				jmp .loop1
			.end1:
		ret



		newLine:
		; 'doctype'
		; new Line
			mov ah, 2
			mov dl, 13	; Carriage return (CR)
			int 21h
			mov dl, 10	; Line feed (LF)
			int 21h
		ret
	section .bss
	 	buffer resb 8
		sebuff resb 8
		answ resb 8
		
;Student: YenShae Fan
;CSCI 361 Spring 2025
;Assignment: Class14 - Procedures, Logical Operations Calculator
;Professor Jakub Pach

;I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced. 
;Any collaboration or use of external resources has been ;properly cited. I am fully aware of the consequences of academic 
;dishonesty and agree to abide by the university's academic integrity policy. I understand the importance the consequences of plagiarism.

;Note, I believe this is working as "a" is correctly being converted to hex 0xBC, but we are using codepage Code page 437 which doesn't not contain the output shown.
org 100h
	global _start
	section .text
		_start:
			mov dx, newline
			call setup ;Sets up the newline string as resb doesn't allow for any predefined chracters.
			;mov ah, 10
			;int 21h
	
			mov dx,inp
			call input
			mov cl,[inp+1]
			cmp cl,10
			jne _end ;Check for less than 10 characters.

			mov ah,9
			mov dx,newline
			int 21h

			mov dx,inp + 2
			int 21h

			mov dx,newline
			int 21h

			mov dx,inp
			call encryp;

			mov dx,inp+2
			int 21h

			_end:
			mov ax, 4c00h
			int 21h

		

		input:
			mov ah,10
			mov bx,dx
			mov cl,11 ;Provides maximum chracters to 0Ah instruction - Manually set to eleven due to 11 - 1(Return character from pressing enter)
			mov [bx],cl ; ^---------------------------------------^
			mov dx, inp ; Loads in pointer to reserved space
			int 21h 
			mov dl, "$" ;Preps null charcter to be inserted into string
			;mov bh,0 ; Not sure if this is necassary but jsut thought to be safe
				
				;Positions the pointer to insert
			mov cx,[bx+1] ;Takes the actual read out bytes and runs checks for greater than 10 
			mov ch,0 ;Makes cx = 4 while keeping with necassary 16 bit register
			add bx,cx 
			mov cx, 2
			add bx,cx

			mov [bx], dl ; Inserts null chracter in with offset of 2 to pass 0AH requirements + bx, the length of the inputted characters.
			ret


		encryp:
			mov bx,dx
			xor di,di

			.loop1:
				cmp di,10
				je .end1
				mov al,[bx + di + 2] ;takes one by
				ror al,4
				xor al,170
				mov [bx+di+2],al
				inc di
				jmp .loop1
			.end1:
				ret


		setup:  ;Inserts characters to create newline string
			mov bx,dx
			mov al, 13
			mov ah,1
			mov [bx], al
			inc bx
			mov al,10 
			mov [bx],al
			mov al,"$"
			inc bx
			mov [bx], al
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
		inp resb 13
		;pre resb 2
		newline resb 3

	section .data
		;newline db 13,10,"$"
		
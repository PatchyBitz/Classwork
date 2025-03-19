;Student: YenShae Fan
;CSCI 361 Spring 2025
;Assignment: Class18.asm - Caesar Cipher with Bit test Operations
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
			;mov cl,[inp+1]
			;cmp cl,10
			;jne _end ;Check for less than 10 characters.

			mov ah,9
			;mov dx,newline
			;int 21h

			;mov dx,inp + 2
			;int 21h

			;mov dx,newline
			;int 21h

			mov dx,inp
			call encryp;

			mov dx,inp
			call outf

			mov ah,9
			mov dx,inp+2
			int 21h

			_end:
			mov ax, 4c00h
			int 21h

		

		input:
			mov ah,10
			mov bx,dx
			mov cl,12 ;Provides maximum chracters to 0Ah instruction - Manually set to eleven due to 12 - 1(Return character from pressing enter)
			mov [bx],cl ; ^---------------------------------------^
			mov dx, inp ; Loads in pointer to reserved space ; Not actually neccasary?
			int 21h 
			mov dl, "$" ;Preps null charcter to be inserted into string
			;mov bh,0 ; Not sure if this is necassary but jsut thought to be safe
				
			;Positions the pointer to insert
			mov cx,[bx+1] ;Takes the actual read out bytes and runs checks for greater than 10 
			
			.chec1: ;Checks for the expected amount of characters
				cmp cl,11
				jne _end 

			mov ch,0 ;Makes cx = 4 while keeping with necassary 16 bit register
			add bx,cx 
			mov cx, 2
			add bx,cx

			mov [bx], dl ; Inserts null chracter in with offset of 2 to pass 0AH requirements + bx, the length of the inputted characters.

			.chec2: ;Checks that final chracter is number
				mov dl,[bx-1] ;Pointer during this state should be at the end of the string pointing at null character
				sub dl,48 ;Converts to number and checks if not single digit int (between 0 and 9)
				cmp dl,9  ;--------^
				ja _end
			ret

		outf: ;Removes last character in string in address in DX register
			mov bx,dx
			xor cx,cx
			mov cl, [bx+1]
			add cl,1
			add bx, cx
			mov dl, "$"
			mov [bx],dl
			ret

		encryp:
			mov bx,dx
			xor di,di
			mov dh,0     ;_______v
			mov dl,[bx+1] ;Preps DX register with just the total amount characters entered
			mov si,dx 	  ;Moves dx register into si index to allow for calculated memory point
			mov cl, [bx + si+1] ;Grabs the last character - Expected to be number.
			sub cl,48

			.loop1:
				cmp di,si
				je .end1
				mov al,[bx + di + 2] ;takes one by
				.checks: ;Originally external medthod, but easier just to build into encryp
					.lowe: ;Checks for lowercase
						mov dl, 97
						cmp al,dl
						jae .hig
			
						jmp .upp ;If lower, will check to see if it is an Uppercase letter already
						.hig:
							mov dl, 122
							cmp al,dl
							jbe .capt ;Effectively returns true that the character is a lowercase letter
							jmp .ct ;If not, this character is not an uppercase or lowercase letter and therefore should be untouched.
					.upp:
						mov dl, 65
						cmp al, dl
						jae .highend
						jmp .ct
						.highend:
							mov dl,90
							cmp al,dl
							ja .ct
							jmp .enc
					.capt:   ;Flips the 3rd bit as that differientiates the upper case and lowercase.
						mov ah,0
						btc ax,5
				
				.enc: ;Only triggers if checks don't jump past it	
					sub al,65 ; Actual encryption block,
					add al, cl
					cmp al, 26
					ja .ovfl
					jb .ovflct 

					.ovfl:
					sub al,26
					cmp al, 26
					ja .ovfl

					.ovflct:
					add al,65

				.ct: ;If jumped to, will skip current chracter			
		
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


		readN: ;Unused
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

		printN: ; Unused
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
		inp resb 14
		;pre resb 2
		newline resb 3

	section .data
		;newline db 13,10,"$"
		
;Student: YenShae Fan
;CSCI 361 Spring 2025
;Assignment: Procedures, ASCII Input Handling, Arithmetic Operations:
;Professor Jakub Pach

;I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced. 
;Any collaboration or use of external resources has been ;properly cited. I am fully aware of the consequences of academic 
;dishonesty and agree to abide by the university's academic integrity policy. I understand the importance the consequences of plagiarism.

org 100h
global _start
section .text

mov ah,1
int 21h
sub al,48
mov [inp],al
mov ah,2
mov dl,[inp]
add dl,48
int 21h
mov dl,13
int 21h
mov dl,10
int 21h

mov cx,[inp]
mov ax, [calc]

call fact
call disp;
_ending:
mov ax, 4C00H
int 21h

fact:
mov bx,[inp]
mul bx
mov [calc],ax
sub byte [inp],1
loop fact
ret

disp:
	mov byte [phold],0
	mov dx,0
		call .ohun
			mov ah,2
			mov dl,[phold]
			add dl,48
			int 21h
			mov byte [phold],0
	mov dx,0
		call .thun
			mov ah,2
			mov dl,[phold]
			add dl,48
			int 21h
			mov byte [phold],0
	mov dx,0
		call .hun
			mov ah,2
			mov dl,[phold]
			add dl,48
			int 21h
			mov byte [phold],0
			mov dx,0
		call .ten
			mov ah,2
			mov dl,[phold]
			add dl,48
			int 21h
mov dl,[calc]
add dl,48
int 21h
ret
	.ohun:
		cmp word [calc],10000
		jb .ohct
		mov dx,[calc]
		sub  word dx,10000
		add byte [phold],1
		mov [calc],dx
		cmp word [calc],10000
		jae .ohun
		.ohct:
		ret
	.thun:
		cmp word [calc],1000
		jb .thct
		mov dx,[calc]
		sub  word dx,1000
		add byte [phold],1
		mov [calc],dx
		cmp word [calc],1000
		jae .thun
		.thct:
		ret
	.hun:
		cmp word [calc],100
		jb .hct
		mov dx,[calc]
		sub word dx,100
		add byte [phold],1
		mov [calc],dx
		cmp word [calc],100;
		jae .hun
		.hct:
		ret
	.ten:
		cmp word [calc],10
		jb .tct
		mov dx,[calc]
		sub word dx,10
		add byte [phold],1
		mov [calc],dx
		cmp word [calc],10
		jae .ten
		.tct:
		ret




_data:
calc dw 1
inp db 0
phold db 0
;Student: YenShae Fan
;CSCI 361 Spring 2025
;Assignment: Simple Calculator with Single-Digit Arguments
;Professor Jakub Pach

;I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced. 
;Any collaboration or use of external resources has been ;properly cited. I am fully aware of the consequences of academic 
;dishonesty and agree to abide by the university's academic integrity policy. I understand the importance the consequences of plagiarism.


org 100h
section .text

global _start

mov ah,1
mov [inp],al
sub [inp],48
mov cx, [inp]
call fact

mov ah,2
mov dl,al
int 21h


_ct:
	mov ax, 4C00H
	int 21h

fact:
	mov ax,1
	mov dx,[inp]
	mul dx
	mov [calc],ax
	ret
	
	

disp:
	\\cmp [inp],10000
	\\jae _tk
	\\call _z
	\\cmp [inp],1000
	\\jge _ok
	\\call _z
	\\cmp [inp],100
	\\jge _oh
	\\call _z
	\\cmp [inp],10
	\\jge _t
	\\call _z
_tk:
	[inp]

_z:
mov ah,2
mov dl,"0"
int 21h
ret
		









section .data
db inp 0
dw calc 1

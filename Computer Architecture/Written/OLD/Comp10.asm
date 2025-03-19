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
int 21h
sub al,48
mov [numf],al ;Number 1
mov al,0
int 21h
sub al,48                   
mov [numb],al ;Number 2
mov ah,2
mov dl,[numf]
add dl, 48
int 21h            ;Setup block - Includes reading input, reprinting them out and then creating newline for output
mov dl,[numb]
add dl,48
int 21h
mov dl,13
int 21h
mov dl, 10
int 21h


addit:
	mov ah, 2
	mov dl, [numf]
	add dl,[numb]
	cmp dl,10
	jge _adds
	mov dh,dl
	mov dl, "0"
	int 21h
	mov dl,dh
	add dl,48
	int 21h
	jmp subtr
_adds:
	sub dl,10
	mov dh,dl
	mov dl,"1"
	int 21h
	mov dl,dh
	add dl,48
	int 21h
	
	
subtr:
	mov dl,32
	int 21h
	mov dl, [numf]
	sub dl, [numb]
	cmp dl, 127
	ja _neg
	mov dh,dl
	mov dl,"0"
	int 21h
	mov dl,dh
	add dl,48
	int 21h
	jmp _mult
_neg:
	mov dl,"N"
	int 21h
	mov dl,"R"
	int 21h


_mult:
	mov dl,32
	int 21h
	mov al, [numb]
	mov dl, [numf]
	mul dl
	mov dl,al
	cmp dl,10
	mov byte [coun],0 
	jge _mults
	mov ah,2
	mov dh,dl
	mov dl,"0"
	int 21h
	mov dl,dh
	add dl,48
	int 21h
	jmp _divs

_mults:
	sub dl,10
	add byte [coun],1
	cmp dl,10
	jge _mults
	mov ah,2
	mov dh,dl
	mov dl,[coun]
	add dl,48
	int 21h
	mov dl,dh
	add dl, 48
	int 21h

_divs:
	cmp byte [numb],0
	je _nn
	mov ah,2
	mov dl,32
	int 21h
	mov dl,"0"
	int 21h
	mov ax,0
	mov dx,0
	mov al,[numf]
	mov bh,[numb]
	div bh      ;This took me half the assignment time and 20 dosbox restarts. All because of register segmentation and how that works.
	mov dh,ah
	mov dl,al
	mov ah,2
	add dl,48;
	int 21h
	mov dl,"0"
	int 21h
	mov dl,dh
	add dl,48
	int 21h
	jmp _ct

	

_nn:	
	mov dl, 32
	int 21h
	mov dl,"N"
	int 21h
	int 21h
	int 21h
	int 21h
	

_ct:
	mov ax, 4C00H
	int 21h

section .data
numf db 0
numb db 0
coun db 0
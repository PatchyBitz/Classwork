;Student: YenShae Fan

;CSCI 361 Spring 2025
;Assignment: Displaying Name Based on Key Press Using DOS Interrupt

;I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced. 
;Any collaboration or use of external resources has been ;properly cited. I am fully aware of the consequences of academic 
;dishonesty and agree to abide by the university's academic integrity policy. I understand the importance the consequences of plagiarism.

org 100h
global _start
section .text
jmp _start

first:
mov ah,2
mov bx, namef
mov dl,[bx]
int 21h
add bx,1
mov dl,[bx]
int 21h
add bx,1
mov dl,[bx]
int 21h
add bx,1
mov dl,[bx]
int 21h
add bx,1
mov dl,[bx]
int 21h
add bx,1
mov dl,[bx]
int 21h
add bx,1
mov dl,[bx]
int 21h
jmp _ending


last:
mov ah,2
mov bx,namel
mov dl,[bx]
int 21h
add bx,1
mov dl,[bx]
int 21h
add bx,1
mov dl,[bx]
int 21h
jmp _ending


_start:
mov ah,1
int 21h

cmp al,65
jge else1
jmp _ending
else1:
cmp al,90
jle last

cmp al,97
jge else2
jmp _ending

else2:
cmp al, 122
jle first

_ending:
mov ax, 4C00H
int 21h

; Code Block
section .data
namef db "Yenshae"
namel db "Fan"

; Data Block

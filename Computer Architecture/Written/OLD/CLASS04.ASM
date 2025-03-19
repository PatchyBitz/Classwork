

;Student: YenShae Fan

;CSCI 361 Spring 2025
;Assignment: DOS Interrupt for Name Printing

;I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced. 
;Any collaboration or use of external resources has been ;properly cited. I am fully aware of the consequences of academic 
;dishonesty and agree to abide by the university's academic integrity policy. I understand the importance the consequences of plagiarism.

org 100h
global _start
section .text
_start:
mov ah,2
mov dl, 'Y'
int 21h
mov dl, 'e'
int 21h
mov dl, 'n'
int 21h
mov dl, 'S'
int 21h
mov dl, 'h'
int 21h
mov dl, 'a'
int 21h
mov dl, 'e'
int 21h
mov dl, ' '
int 21h
mov dl, 'F'
int 21h
mov dl, 'a'
int 21h
mov dl, 'n'
int 21h  
mov ax, 4C00H
int 20h
; Code Block
section .data
; Data Block
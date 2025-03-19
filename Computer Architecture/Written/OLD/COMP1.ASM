

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
mov dl, 10
int 21h

mov dh,[name]
mov dl,dh
int 21h
inc dh
mov dl,dh
int 21h
mov ax, 4C00H
int 21h
; Code Block
section .data
name dw 6559h

; Data Block
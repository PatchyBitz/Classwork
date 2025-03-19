org 100h
global _start
section .text
_start:
mov al, 10
mov bl, 2
div bl
mov dl,al
mov ah,2
int 21h
mov ax, 4C00H
int 21h
; Data Block
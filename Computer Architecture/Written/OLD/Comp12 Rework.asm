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
    mov ch, 0
    mov cl,[inp]
    mov ax, [calc]
    call fact
    call disp;
_ending:
    mov ax, 4C00H
    int 21h
fact:   ;Factorial routine
    mov bh,0
    mov bl,[inp]
    mul bx
    mov [calc],ax
    mov dl,1
    sub [inp],dl
    loop fact
    ret
disp:     ;Display routine
    mov dh,0
    mov [phold],dh
    mov dl,0
    mov dh,0
        call .ohun
            mov ah,2
            mov dl,[phold]
            add dl,48
            int 21h
    mov dl,0
    mov dh,0
    mov [phold],dh
        call .thun
            mov ah,2
            mov dl,[phold]
            add dl,48
            int 21h
    mov dl,0
    mov dh,0
    mov [phold],dh
        call .hun
        mov ah,2
        mov dl,[phold]
        add dl,48
        int 21h
    mov dl,0
    mov dh,0
    mov [phold],dh ; Was mov byte [phold],0
        call .ten
            mov ah,2
            mov dl,[phold]
            add dl,48
            int 21h
    mov dl,[calc]
    add dl,48
    int 21h
    ret
.ohun: ;One hundred thousand place ; I looked into it an it looks like I'm doing a direct memory to memory action without a register intermediary.
    mov ax, 10000
    cmp [calc],ax   
    jb .ohct
    mov dx,[calc]
    sub word dx,10000
    mov al, 1 
    add [phold],al
    mov [calc],dx
    mov ax, 10000
    cmp [calc],ax
    jae .ohun
.ohct:     ;One hundred thousand place continue block
    ret
.thun:  ;Thousand place
    mov ax, 1000
    cmp [calc],ax   
    jb .thct
    mov dx,[calc]
    sub word dx,1000
    mov ax, 1 
    add [phold],ax
    mov [calc],dx
    mov ax, 10000
    cmp [calc],ax
    jae .thun
.thct:  ;Thousand place continue block
    ret
.hun: ;Hundred place
    mov ax, 100
    cmp [calc],ax   
    jb .hct
    mov dx,[calc]
    sub word dx,100
    mov al, 1 
    add [phold],al
    mov [calc],dx
    mov ax, 10000
    cmp [calc],ax
    jae .hun
.hct: ;Hundred continue block
    ret
.ten: ;Tens block
    cmp word [calc],10
    jb .tct
    mov dx,[calc]
    sub word dx,10
    add byte [phold],1
    mov [calc],dx
    cmp word [calc],10
    jae .ten
.tct: ;Tens continue block
    ret
_data:
    calc dw 1
    inp db 0
    phold db 0
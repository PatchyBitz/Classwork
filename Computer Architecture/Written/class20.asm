;Student: YenShae Fan
;CSCI 361 Spring 2025
;Assignment: Class20.asm - Procedures, the Stack, Arithmetic Operations
;Professor Jakub Pach

;I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced. 
;Any collaboration or use of external resources has been ;properly cited. I am fully aware of the consequences of academic 
;dishonesty and agree to abide by the university's academic integrity policy. I understand the importance the consequences of plagiarism.

;Note, I believe this is working as "a" is correctly being converted to hex 0xBC, but we are using codepage Code page 437 which doesn't not contain the output shown.
org 100h
	global _start
	section .text
		_start:


            mov ah,1
            int 21h

            mov ah,2
            mov dl,al
            int 21h

            sub al,48
            sub sp,2
            mov bp,sp
                mov ah,0
                mov [bp],ax
                call _fact
                mov bx,ax
            add sp,2


            sub sp,2
            mov bp,sp
            mov [bp],bx
            call _outp2
            add sp,2


            jmp _end

            _fact:
                mov bp,sp ;Returns BP to Sart of stack
                mov cx,[bp+2]
                mov ch,0
                mov ax,cx
                mov ah,0
                .mainl:                    
                    sub cx,1
                    cmp cl,0
                    jz ._end
                    mul cx
                    jmp .mainl
                    ._end:
                        ret
            
            _outp1:
                mov bp,sp
                mov [bp-2],bx
                mov ax,[bp+2]
            

                xor dx,dx
                xor cx,cx
                mov bx,10
                cmp ax,10
                jb .end

                .digi:
                    add cl,1
                    xor dx,dx
                    div bx
                    cmp ax,10
                jae .digi
                

                .end:
                    add cl,1
                    mov bx,[bp-2]
                    mov ah,2
                    mov dl,13
                    int 21h
                    mov dl,10
                    int 21h
                    mov dl,cl
                    add dl,48
                    int 21h 
                ret

            _outp2:
                mov bp,sp
                xor dx,dx
                sub bp,4
                mov [bp],bx ;Preserve bx register
                mov bx,10
                mov ax,[bp+6]
        
                xor cx,cx

                .main1:
                    inc cl
                    xor dx,dx
                    div bx
                    xor dh,dh
                    sub bp,4
                    mov [bp],dx
                    cmp ax,0
                    jnz .main1

                .end:
                    mov ah,2
                    mov dl,13
                    int 21h
                    mov dl,10
                    int 21h
                    .disp:
                        mov dx,[bp]
                        add bp,4
                        xor dh,dh
                        add dl,48
                        int 21h
                        dec cl
                        cmp cl,0
                        jnz .disp

                    mov bx,[bp+2] ;returns preserved bx register.
                    ret
                
                

			_end:
			mov ax, 4c00h
			int 21h
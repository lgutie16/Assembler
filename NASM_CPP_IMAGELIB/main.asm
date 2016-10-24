bits 32
global _start

sys_exit        equ     1
sys_read        equ     3
sys_write       equ     4
stdin           equ     0
stdout          equ     1
stderr          equ     3

SECTION     .data
filename    db      "File Name?"
lenf        equ     $-filename
message     db      "message" 
lenm        equ     $-message

SECTION     .bss
lpBuffer     resb    5
Buf_Len      equ     $-lpBuffer

Buf          resb    1

SECTION     .text
    
_start:
    mov     ecx, filename
    mov     edx, lenf
    call    DisplayText

    mov     ecx, lpBuffer
    mov     edx, Buf_Len
    call    ReadText
    push    eax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;    
    cmp     eax, Buf_Len
    jl      Good

    cmp     byte [ecx + edx - 1], 10
    je      Good
    mov     byte [ecx + edx - 1], 10
    call    ClearTerminal
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;   
Good:
    mov     ecx, message
    mov     edx, lenm
    call    DisplayText
    
    pop     edx
    mov     ecx, lpBuffer
    call    DisplayText
    
    jmp     Exit
    
ClearTerminal:   
    mov     edx, 1
    mov     ecx, Buf
    mov     ebx, stdin
    mov     eax, sys_read
    int     80h     
    cmp     byte [ecx + edx - 1], 10
    jne     ClearTerminal
    ret
    
DisplayText:
    mov     eax, sys_write
    mov     ebx, stdout
    int     80H 
    ret
    
ReadText:
    mov     ebx, stdin
    mov     eax, sys_read
    int     80H
    ret

Exit:  
    mov     eax, sys_exit
    xor     ebx, ebx
    int     80H
bits 32
global proceso
extern  sort

section .text  ; start of the "CODE segment"

proceso: 
	push ebp          ; setup stack
    mov ebp,esp 

    ; put parameters into registers
    mov ebx, [ebp+12] ; array
    mov edx, [ebp+8]  ; len

    push ebx
    push edx
    call sort
    pop eax
    ret
bits 32
global proceso
extern  sort

section .text              ; start of the "CODE segment"

proceso: 
 %define a [ebp]
 %define n [ebp + 12]
 enter 0, 0
 pusha
 mov ecx, 1
 for:
   add eax, n
   push edx
   push eax
   call sort
   pop eax
 ret 
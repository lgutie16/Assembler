bits 32
global proceso
extern  printf

section .text              ; start of the "CODE segment"

proceso: 
 %define a [ebp + 8]
 %define n [ebp + 12]
 enter 0, 0
 pusha
 mov ecx, 1
 for:
   mov ebx, ecx
   imul ebx, 4
   add ebx, a
   mov ebx, [ebx]
   mov edx, ecx
   dec edx
   while:
     cmp edx, 0
     jl while_quit
     mov eax, edx
     imul eax, 4
     add eax, a
     cmp ebx, [eax]
     jge while_quit
     mov esi, [eax]
     mov dword [eax + 4], esi
     dec edx
     jmp while
   while_quit:
   mov [eax], ebx
   inc ecx
   cmp ecx, n
   jl for
 popa
 leave
 ret
include io.h

.model small
.stack 200h

arrayLength equ 4

.data
str1 	db 		50 dup(?)
arrw   	dw      arrayLength dup(?)
crlf    db 		10,13,0

.code

sort proc
for2:
		
		s2:	cmp [si],ax
			jg big
			jmp edame
		big:
			mov  bx,[si]
			mov [si],ax
			mov [di],bx
		edame:
		cmp ax,0
		jnz sd
		jmp s0
		sd:
		add si,2
		add di,2
		mov   ax,[di]
		jmp edame2
		s0:
		mov   si, offset arrw
		mov   di, si
		add   di,2
		mov   ax,[di]
	edame2:
loop for2
ret
sort endp


Main   proc
       mov ax, @data
	   mov ds, ax
	   ;---------------------------
	   mov   si, offset arrw
	   mov   cx, arrayLength
for1:	   
	   inputs    str1,5 
	   output crlf
	   atoi      str1     
	   mov       [si], ax
	   add       si, 2
	   loop  for1
	   
    mov bx,arrayLength
while1: cmp bx,0
		jbe endwhile1
	mov   si, offset arrw
	mov   di, si
	add   di,2
	mov   ax,[di]
	mov cx,arrayLength
	sub bx,1
call sort 
jmp while1
endwhile1:
	   
	   output  crlf
	   mov   si, offset arrw
	   mov   cx, arrayLength
for3:	   
	   itoa   str1,[si]
	   output  crlf
	   output  str1
	   add si,2
	   loop   for3
		
	   ;---------------------------
	   mov   ax,4c00h
	   int 21h
Main   endp
       end   Main
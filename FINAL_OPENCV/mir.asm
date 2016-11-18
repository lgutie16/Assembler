numargs     equ 3
sys_exit    equ 1
sys_read    equ 3
sys_write   equ 4
stdin       equ 0 
stdout      equ 1
stderr      equ 3	

extern      printf
extern      puts
extern      loadimg
extern      saveimg
extern      getdims
extern 		gettextdims
extern      getdats
extern      pixchange
extern      getdifference
extern 		writeimage
extern 		writeresize


SECTION .data
	testfmt:    db  "%s %s", 10, 0 
	infail:     db  "The input file route %s is invalid.", 10, 0  
	outfail1:   db  "The output file route %s is invalid.", 10, 0	
	outfail2:   db  "The output file route %s is protected, change permissions.", 10, 0
	argfail:    db  "The number of arguments is different to 2.", 10, 0
	nofit:    	db  "Text Doesn't fit recalculating.", 10, 0
	c:          dd  0   				 ;column iterator
	r:          dd  0   				 ;row iterator
	k:          dd  0   				 ;channel iterator
	;declaring NASM variables

SECTION .bss
	arg1:		resd	1
	arg2:		resd	1
	numa:		resd	1
	dats:		resq	1
	cols:		resd	1
	colm:		resd	1
	rows:		resd	1
	pix1:		resd	1
	pix2:		resd	1
	width		resd	1
	height		resd	1
										;reserving memory space for variables that will be brought from C++	
	
SECTION	.text
global 	main

main:
	mov     ecx, [esp + 4] 				;number of arguments 
	mov     [numa], ecx    				;store this value

	mov     edx, [esp + 8] 				;pointer to start of argument array
	mov     eax, dword[edx + 4] 		;store the first two arguments
	mov     [arg1], eax
	mov     eax, dword[edx + 8]
	mov     [arg2], eax
 	


	cmp     dword[numa], numargs 		;compare the number of arguments
				     					;..received against the expected number
	jne     nicht 						;its different
	je      jah   						;its the same


nicht:
	push    argfail 					;failing message, number of arguments is greater
	call    printf  					;..than the two expected arguments
	jmp     exit

jah:
	push    dword[arg1] 				;puts into the stack the input route
	call    loadimg 					;calls the external function that loads an image
										;.. and it returns a value depending on what happens
	cmp     eax,0   					;whatever that function returns is stored in eax
										;in this case we are checking if it returns 0 = failure
										;or if returns 1 = success at loading the image	
	jne     calcsize
	je      fail1   


calcsize:
	push    dword[arg2]
	call 	gettextdims
	cmp     eax, 0            			;whatever is returned is storage in eax
	jne     success 					;if is no 1 is because text doesn't fit 
	je      resizetext
	;mov     ecx, [eax]
	;mov     [width], ecx
	;mov     ecx, [eax + 4]
	;mov     [height], ecx

	
	;cmp 	dword[cols], ecx   			;does the text fit over image frame	horizontaly
	;jne     resizetext 
	;je      jah


resizetext:
	push    nofit 						;advice message, message doesn't fit
	call    printf  					
	call 	getdifference
	push 	eax
	call   	writeresize
	push    dword[arg2] 				;write text over image
	call    writeimage
	cmp 	eax, 0
	je      exit
	jne     exit 


fail1:
										;fail1 is a failure for an invalid input route
	push    dword[arg1]
	push    infail
	call    printf
	jmp     exit

fail2:
										;fail2 is a failure for an invalid output route
	push    dword[arg2]
	push    outfail1
	call    printf
	jmp     exit

fail3:
										;fail3 is a failure for a protected output route
	push    dword[arg2]
	push    outfail2
	call    printf
	jmp     exit

success:
	push    dword[arg2] 				;write text over image
	call    writeimage 	
	call    getdims 					;returns a pointer to an array with rows and cols values
	mov     ecx, [eax]
	mov     [cols], ecx
	mov     ecx, [eax + 4]
	mov     [rows], ecx
	
save:
	push    dword[arg2]
	call    saveimg
	cmp     eax, 0
	je      fail2
	cmp     eax, 2
	je      fail3
	jne     exit

exit:
	mov     eax, sys_exit
	int		0x80
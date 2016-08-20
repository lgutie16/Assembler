#SimuProc 1.4.3.0


MSG '1 = INGRESAR N'
MSG '2 = INGRESAR VALORES DE LA ECUACIÓN'
MSG '3 = GENERAR LOS N NUÚMEROS ALEATORIOS'
MSG '4 = MOSTRAR LOS NÚMEROS GENERADOS'

MSG '****  VALORES POR DEFECTO: "1"  ****'
;------------------------------------------------------------------------

; selección de operación
MSG
  LDT 'INGRESE SELECCIÓN'
  CMP 80 ;Comparamos  con el # preestablecido en memoria 80, que es 1.
  JEQ 40 ;Si son iguales salte a la memoria 40 ejecute a partir de ahí.
         ; de lo contrario ...
  CMP 81 ;Comparamos  con el numero preestablecido en memoria 81, que es 2.
  JEQ 04d  ;Si son iguales salte a la memoria 50 ejecute a partir de ahí.
        ; de lo contrario ...
  CMP 82  ;Comparamos  con el numero preestablecido en memoria 82, que es 3.
  JEQ 65  ;Si son iguales salte a la memoria 60 ejecute a partir de ahí.
        ; de lo contrario ...
  CMP 83  ;Comparamos con el numero preestablecido en memoria 83, que es 4.
  JEQ 120 ;Si son iguales salte a la memoria 70 ejecute a partir de ahí.
  ; de lo contrario ...
  CMP 84  ;Comparamos con el numero preestablecido en memoria 84, que es 0.
  JEQ 180  ;Si son iguales salte a la memoria 70 ejecute a partir de ahí.
  ; de lo contrario ...
   MSG 'ERROR DE DIGITACION INTENTELO DE NUEVO';Imprima mensaje de errror
  JMP 0 ;Salta incondicionalmente y presenta nuevamente el menu seleccion

;--------------------------------------------------------------------------

#40
ldt ingrese n
sta 01a
mov cx,01a
jmp 000

#04d
msg "Ingrese a "
in ax,1
stf 15
msg "Ingrese b "
in ax,1
stf 100
msg "Ingrese m "
in ax,1
stf 110
msg "Ingrese xn " ; variable de recurrencia
in ax,1
stf 20
jmp 000


#65
;mov bx,102
mulf 15
addf 100
mov 89,cx ;Aseguro cx (control ciclo)
divf 110
mov ax,cx ; muevo modulo a ax para hacer itof
itof ; lo paso a ieee bx ax con itof
mov 86,ax ; aseguro ax (val ciclo)
mov 87,bx ; aseguro bx (val ciclo)
mov cx,89 ; le doy el val del ciclo a ax
mov ax,cx ; aseguro el espacio donde se guardará bx con la mul
mul 81    ; multiplico * 2
mov bx,ax ; controlo el ciclo con bx
mov ax,86 ; guardo ax
stb 185 ; se guarda en 185 + bx
mov ax,bx
sub 80  ; resto 1
mov bx,ax
mov ax,87 ; guardo bx
stb 185
mov ax,86
mov bx,87
mov cx,89
loop 065
jmp 000

#120
mov cx,01a
mov ax,cx
mul 81
sub 80
mov bx,ax
ldb 185
out 1,ax
loop 121
jmp 000

#180
hlt  ; Control de ejecución (controlado)

;control del menú
#80
0001   ; Asignamos el valor de 1 a memoria 80
0010   ; Asignamos el valor de 2 a memoria 81
0011   ; Asignamos el valor de 3 a memoria 82
0100   ; Asignamos el valor de 4 a memoria 83
0101   ; Asignamos el valor de 5 a memoria 85

#084
0

#102
0001
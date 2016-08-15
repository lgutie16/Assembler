#SimuProc 1.4.3.0


MSG '******  MENU  ******'
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
  JEQ 50  ;Si son iguales salte a la memoria 50 ejecute a partir de ahí.
        ; de lo contrario ...
  CMP 82  ;Comparamos  con el numero preestablecido en memoria 82, que es 3.
  JEQ 60  ;Si son iguales salte a la memoria 60 ejecute a partir de ahí.
        ; de lo contrario ...
  CMP 83  ;Comparamos con el numero preestablecido en memoria 83, que es 4.
  JEQ 70  ;Si son iguales salte a la memoria 70 ejecute a partir de ahí.
  ; de lo contrario ...
  CMP 84  ;Comparamos con el numero preestablecido en memoria 83, que es 4.
  JEQ 80  ;Si son iguales salte a la memoria 70 ejecute a partir de ahí.
  ; de lo contrario ...
   MSG 'ERROR DE DIGITACION INTENTELO DE NUEVO';Imprima mensaje de errror
  JMP 0 ;Salta incondicionalmente y presenta nuevamente el menu seleccion

;--------------------------------------------------------------------------

#40
ldt ingrese n ; Cantidad de valores a generar
sta 01a
mov cx,01a
jmp 000

#50
ldt introduzca a
sta 10
ldt introduzca xn ; variable de recurrencia
sta 20
ldt introduzca b
sta 100
ldt introduzca m
sta 101
jmp 000

#60
mov bx,102
mov ax,20 ; variación de variable de recurrencia
mul 10
add 100
div 101
mov ax,bx
mov bx,cx  ; manejo de posiciones de memoria con BX
stb 085 ; almacenamiento de valores
loop 062
jmp 000


#70
mov cx,01a
mov bx,102
mov bx,cx ; manejo de posiciones de memoria con BX
ldb 085  ; Impresión de valores almacenados
eap
loop 072
jmp 000



#80
hlt  ; Control de ejecución (controlado)

hlt  ; Control de ejecución (No controlado)



;-----------------------------------------------------------------------------

; Asignaciones preestablecidas
;control del loop
#102
0001

#046
0001

#045
0001

#01a
0001

#010
0001

#020
0001

#100
0001

#101
0001


;control del menú
#80
0001   ; Asignamos el valor de 1 a memoria 80
0010   ; Asignamos el valor de 2 a memoria 81
0011   ; Asignamos el valor de 3 a memoria 82
0100   ; Asignamos el valor de 4 a memoria 83
1010   ; Asignamos el valor de 4 a memoria 84


;Donde queda almacenado el ultimo valor de que queda en memoria

;como mostrar bx por pantalla



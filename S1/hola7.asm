pila segment stack 'stack'
	dw 100h dup (?)
pila ends
datos segment 'data'
	msg db 'hola mundo$'
datos ends
codigo segment 'code'
	assume cs:codigo, ds:datos, ss:pila
	main PROC
		mov ax,datos
		mov ds,ax
        
		; Imprimir 7 veces la cadena
		mov cx,0
		bucle:
			mov dx, OFFSET msg
			mov ah,9
			int 21h
			; actualizar el contador y comprobar la condicion
			inc cx
			cmp cx,7
			jne bucle
		; Terminar y salir
		mov ax,4C00h
		int 21h
	main ENDP
codigo ends
END main

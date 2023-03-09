//#include <mi_io.h>

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <dos.h>

#define BYTE unsigned char

BYTE MODOTEXTO = 3;
BYTE MODOGRAFICO = 4;

//Colores
/*
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
*/

int i,j;

void _gotoxy(int x, int y){
    union REGS inregs, outregs;

    inregs.h.ah = 0x02; //Asigna posicio del cursor 
    inregs.h.dh = x; //Fila
    inregs.h.dl = y; //Columna
    inregs.h.bh = 0; //Pagina

    int86(0x10,&inregs,&outregs);
}
void _setcursortype(int tipo_cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(tipo_cursor){
		case 0: //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case 1: //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case 2: //grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	}
	int86(0x10, &inregs, &outregs);
}

void _setvideomode(BYTE mode){
    union REGS inregs, outregs;

    inregs.h.ah=0x00; //Activar modo de video
    inregs.h.al=mode; //Modo
    int86(0x10, &inregs, &outregs);
}
/**
 * @brief MODIFIFARRRRRRRRRR
 * 
 * @return BYTE 
 */
BYTE _getvideomode(){
    union REGS inregs, outregs;
    int modo;
    inregs.h.ah=0xF;
    inregs.h.al=modo;

    int86(0x10, &inregs, &outregs);

    return outregs.h.al;

    /*if (x == 0x03){
        printf("\nModo texto");
    }else if (x == 0x02){
        printf("\nModo samba");
    }else if (x == 0x01){
        printf("\nmodo epico");
    }else if (x== 0x04){
        printf("\nmodo grafico");
    }else{
        printf("\nmodo raro");
    }*/
}

/**
 * @brief Cambia el color de un char
 * 
 * @param color Color
 * @param c Char
 */
void _charcolor(int color, const char c){
    union REGS inregs, outregs;
    inregs.h.ah=0x09;
    inregs.h.al=(int) c;
    inregs.h.bl=color;
    inregs.h.bh=0x00;
    inregs.x.cx=1; 
    int86(0x10, &inregs, &outregs);
}

/**
 * @brief Escribe una cadena de un color
 * 
 * @param color Color de la cadena
 * @param str Cadena
 */
void _textcolor(int color, const char * str){
    for( i = 0; i < strlen(str);i++ ){ 
        _charcolor(color,str[i]);
        printf("%c", str[i]); 
    }
    printf("\n");
}


void _textbackground(int color){
    union REGS inregs, outregs;

    inregs.h.ah=0x0B;
    //inregs.h.al=98; // 'a'
    inregs.h.bl=color;
    inregs.h.bh=0x00;
    //inregs.x.cx=10; //Numero de veces que se repite 

    int86(0x10, &inregs, &outregs);
}
void _clrscr(void){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

/**
 * @brief Escribe un caracter en pantalla con el color actual
 * 
 * @param c 
 */
void _cputchar(char c){
    union REGS inregs, outregs;
    inregs.h.ah = 2;
    inregs.h.dl = c;
    int86(0x21, &inregs, &outregs);
}

/**
 * @brief Obtiene un caracter del teclado y lo muestra en pantalla
 * 
 * @return int 
 */
int _getchar(){
	union REGS inregs, outregs;
	int caracter;

	inregs.h.ah = 1;
	int86(0x21, &inregs, &outregs);

	caracter = outregs.h.al;
	return caracter;
}
/*
int _getche(){
    printf("\nPulsa una tecla... ");
	int tmp = _getchar();

	printf("\nHas pulsado: ");
	_putchar( (char)tmp );
}*/

/**
 * @brief Pinta un pixul en las coordenadas x,y del color c
 * 
 * @param x Coordenada x
 * @param y Coordenada y
 * @param c Color del pixel
 */
void pixel(int x, int y, BYTE c){
    union REGS inregs, outregs;
    inregs.x.cx = x;
    inregs.x.dx = y;
    inregs.h.al = c;
    inregs.h.ah = 0x0C;
    int86(0x10, &inregs, &outregs);
}

void _pausa(){
    union REGS inregs, outregs;
    inregs.h.ah = 0x00; //Leer pulsacion de tecla
    int86(0x16, &inregs, &outregs);
}

void printCube(int begin, int size){
    _setvideomode(MODOGRAFICO);
    
    for(i = begin; i < size; i++){ 
        pixel(i,begin,1);
        //pixel(10,i,2);
        pixel(i,size,1);    
    }

    for(i = begin; i <= size; i++){ 
        pixel(begin,i,2);
        pixel(size,i,2);    
    }
    _pausa();
    _setvideomode(MODOTEXTO);
}

int size = 700;
const char * str;
int main(void){
    cprintf( "Ejemplo de \"textbackground\" y \"textcolor\"\r\n\r\n" );
   
   str = "HOLA";
   _textbackground(3);
   cprintf( "Ejemplo de \"textbackground\" y \"textcolor\"\r\n\r\n" );
   _textbackground(3);
   printf( "Ejemplo de \"textbackground\" y \"textcolor\"\r\n\r\n" );
   _textcolor(2,str);
    _pausa();
   printCube(10,size);

   return 0;

}
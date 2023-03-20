//#include <mi_io.h>

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <dos.h>

#define BYTE unsigned char

BYTE MODOTEXTO = 3;
BYTE MODOGRAFICO = 4;

unsigned int fontColor;
unsigned int backGroundColor;

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
void _textcolor(int color){
    /*for( i = 0; i < strlen(str);i++ ){ 
        _charcolor(color,str[i]);
        printf("%c", str[i]); 
    }
    printf("\n");
    */
   fontColor = color;

}


void _textbackground(int color){
    /*union REGS inregs, outregs;

    inregs.h.ah=0x0B;
    //inregs.h.al=98; // 'a'
    inregs.h.bl=color;
    inregs.h.bh=0x00;
    //inregs.x.cx=10; //Numero de veces que se repite 

    int86(0x10, &inregs, &outregs);*/
    backGroundColor = color;
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
    inregs.h.bl= backGroundColor << 4 | fontColor;
    inregs.h.dl = c;
    int86(0x21, &inregs, &outregs);
}
void _cputchar2(int c){
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = c;
    inregs.h.bl= backGroundColor << 4 | fontColor;
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;
    int86(0x10, &inregs, &outregs);
    return;
}

void _printf(const char *cadena){
    //printf("%s",cadena);
    for(i = 0; i <= strlen(cadena); i++){
        printf("%c", cadena[i]);
        _cputchar2((int) cadena[i]);
    }
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

void _putchar(char c){
    union REGS inregs, outregs;

	inregs.h.ah = 2;
	inregs.h.dl = c;
	
    int86(0x21, &inregs, &outregs);

}

void _getche(){
    int tmp;
    printf("\nPulsa una tecla... ");
	tmp = _getchar();

	printf("\nHas pulsado: ");
	_putchar( (char)tmp );
}

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

void _printCube(int begin, int size){
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

/*
algoritmo Bresenham
*/
int dx,dy,sx,sy,err,e2;
void _drawLine(int x1, int y1,int x2, int y2,int color){
    dx = abs(x2-x1);
    dy = abs(y2-y1);
    
    if (x1 < x2) 
        sx = 1;
    else sx = -1;

    if (y1 < y2)
        sy = 1;
    else sy = -1;
    
    err = dx - dy;

    while(1){
        pixel(x1, y1,color);
        
        if (x1 == x2 && y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 > -dy){
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx){
            err += dx;
            y1 += sy;
        }
    }
}


void _drawShapeTextColor(int x1, int y1, int x2, int y2, int colorFont, int colorBack){
    union REGS inregs, outregs;

  inregs.h.ah = 0x06; //Scroll up window
  inregs.h.al = 0; //Lineas de scroll (0 = borrar)
  inregs.h.bh = colorBack << 4 | colorFont; // Atributo de las líneas en blanco
  /*
  CH = Fila inicial de scan, CL = Fila final de scan
  DH = Fila, DL = Columna
  */
  inregs.h.ch = x1; 
  inregs.h.cl = y1; 
  inregs.h.dh = x2;
  inregs.h.dl = y2;

  int86(0x10, &inregs, &outregs);
}

void _drawCubeVideoColor(int x, int y, int color){
    union REGS inregs, outregs;
    BYTE ret;

    if((ret = _getvideomode()) != MODOGRAFICO){
        _setvideomode(MODOGRAFICO);
    }
    
    for(i = x; i < y; i++){
        pixel(x,i,color);
        pixel(y,i,color);
    }

    for(i = x; i <= y; i++){
        pixel(i,x,color);
        pixel(i,y,color);
    }
    
    /*_pausa();
    _setvideomode(0x03);*/
}


int size = 700;
const char * str;
int main(void){
    int temp;
    printf("Comprobacion de funciones:\n");
    _clrscr();
    printf("Colocando el cursor en una posicion: \n");
    //_pausa();
    //Conjunto para pintar "P1"
    _gotoxy( 0x02,0x15);
    printf("*\n");
    _gotoxy( 0x02,0x16);
    printf("*\n");
    _gotoxy( 0x02,0x17);
    printf("*\n");
    _gotoxy( 0x03,0x18);
    printf("*\n");
    _gotoxy( 0x04,0x17);
    printf("*\n");
     _gotoxy( 0x04,0x16);
    printf("*\n");


    _gotoxy( 0x03,0x15);
    printf("*\n");
    _gotoxy( 0x04,0x15);
    printf("*\n");
    _gotoxy( 0x05,0x15);
    printf("*\n");
    _gotoxy( 0x6,0x15);
    printf("*\n");

    
    _gotoxy( 0x04,0x23);
    printf("*\n");
    _gotoxy( 0x03,0x22);
    printf("*\n");
    _gotoxy( 0x02,0x23);
    printf("*\n");
    _gotoxy( 0x03,0x23);
    printf("*\n");
    _gotoxy( 0x04,0x23);
    printf("*\n");
    _gotoxy( 0x05,0x23);
    printf("*\n");
    _gotoxy( 0x6,0x23);
    printf("*\n");

    
    
    printf("Pulsa una tecla: \n");
    temp=_getchar();

    printf("\nHas pulsado: ");
    _cputchar((char)temp);
    printf("\nIgual con el getche\n");
    _getche();

    printf("\nCursor invisible: ");
    _setcursortype(0);
    _pausa();
    printf("\nCursor normal: ");
    _setcursortype(1);
    _pausa();
    printf("\nCursor grueso: ");
    _setcursortype(2);
    _pausa();

    //Volvemos al cursor normal
    _setcursortype(1);

    _textcolor(0x02);
    _textbackground(0x03);

    _printf("\nProbando el cambio de color de letra y fondo");
    _pausa();
    _clrscr();

    _drawShapeTextColor(3,3,10,10,1,4);
    _pausa();
    _clrscr();

    _printCube(0x03, 100);
    _drawCubeVideoColor(10,100,0x01);
    _drawCubeVideoColor(50,150,0x02);
    _drawLine(10,10,50,50,0x03);
    _drawLine(10,100,50,150,0x03);
    _drawLine(100,100,150,150,0x03);
    _drawLine(100,10,150,50,0x03);
    
    _pausa();
    _setvideomode(0x03);
    


   return 0;

}
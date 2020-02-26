#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <pic16f887.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCD8bits.h"


void Lcd_Cmd(uint8_t z)
{
	PORTBbits.RB6 = 0;          //RS = 0
	PORTD = z;                  //Data transfer
	PORTBbits.RB7  = 1;         //Clock para activar el pin E
    __delay_ms(4);
    PORTBbits.RB7  = 0;             
}

void Lcd_Clear(void)
{
	Lcd_Cmd(0);
	Lcd_Cmd(1);
}

void Lcd_Set_Cursor(uint8_t x, uint8_t y)
{
	char temp;
	if(x == 1)
	{
	  temp = 0x80 + y - 1;
      Lcd_Cmd(temp);
	}
	else if(x == 2)
	{
		temp = 0xC0 + y - 1;
		Lcd_Cmd(temp);
	}
}

void Lcd_Init(void)                 //Funcion de inicializacion de la pantalla LCD
{
  __delay_ms(15);
  Lcd_Cmd(0x030);
	__delay_ms(5);
  Lcd_Cmd(0x030);
	__delay_ms(11);
  Lcd_Cmd(0x030);
  __delay_ms(160);
  /////////////////////////////////////////////////////
  Lcd_Cmd(0x38);
  //Lcd_Cmd(0x10);
  Lcd_Cmd(0x01);
  Lcd_Cmd(0x06);
  Lcd_Cmd(0x0C);
 }

void Lcd_Write_Char(char a)
{
   PORTBbits.RB6 = 1;         //RS = 1
   PORTD = a;                 //Data transfer
   PORTBbits.RB7 = 1;         //Clock para activar el pin E
   __delay_us(40);
   PORTBbits.RB7 = 0;
}

void Lcd_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Write_Char(a[i]);
}

void Lcd_Write_Number(uint8_t var){
    char str[4];                        //Funcion para excribir un numero entero en la pantalla
    sprintf(str, "%d", var);
    Lcd_Write_String(str);
}


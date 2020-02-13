/*
 * File:   main.c
 * Author: jeffr
 *
 * Created on February 7, 2020, 11:55 AM
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)



#include <xc.h>

#define _XTAL_FREQ 4000000


#include <stdint.h>
#include <pic16f887.h>
#include "ADC.h"
#include "LCD8bits.h"
#include "USART.h"

//Protoripos de funciones
void init(void);

float pot1 = 0;
float pot2 = 0;
uint8_t adc = 0;
uint8_t ent1 = 0, ent2 =0, dec1 = 0, dec2 = 0, datos = 0, cont = 0;
float deci1 = 0, deci2 = 0;






//Vector de interrupcion

void __interrupt() ISR(void){
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
    if (PIR1bits.ADIF == 1){
        adc = 1;                //Se levanta un bandera cuando el ADC entre a la interrupcion
        PIR1bits.ADIF = 0;

    }
    
    if (PIR1bits.RCIF == 1){
        datos = RCREG;          //Se transfieren los datos del RCREG a una variable
    }
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

void main(void) {
//    INTCONbits.GIE = 1;
//    INTCONbits.PEIE = 1;
    init();                     //Se inicializan todas las librerias
    serial();
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("POT1");
    Lcd_Set_Cursor(1, 6);
    Lcd_Write_String("POT2");
    Lcd_Set_Cursor(1, 11);
    Lcd_Write_String("CONT");
    
    while(1){
        ADC1();                 //Se inicializa el ADC para el puerto A0 y se transfieren los datos 
        if(adc == 1){           // de ADRESH a una variable 
            pot1 = ADRESH;
            adc = 0;
            ADCON0bits.GO_DONE = 1;
        }
        pot1 = (pot1)* 5/255;       //Se realiza un mapeo para los valores del ADRESH y se separa 
        ent1 = pot1;                //en dos enteros para poder desplegarlos como la parte entera y decimal del voltaje
        deci1 = (pot1 - ent1) * 100;
        dec1 = deci1;
        
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_Number(ent1);
        Lcd_Write_Char(".");
        Lcd_Write_Number(dec1);

               
        ADC2();                     //Se realiza un mapeo para los valores del ADRESH y se separa 
         if(adc == 1){              //en dos enteros para poder desplegarlos como la parte entera y decimal del voltaje
            pot2 = ADRESH;          
            adc = 0;
            ADCON0bits.GO_DONE = 1;
        }
        pot2 = (pot2)* 5/255;
        ent2 = pot2;
        deci2 = (pot2 - ent2) * 100;
        dec2 = deci2;
        Lcd_Set_Cursor(2, 7);
        Lcd_Write_Number(ent2);
        Lcd_Write_Char(".");
        Lcd_Write_Number(dec2);
        __delay_ms(10);
        
        
        if (datos == 43 ){          //Se reviza que valor de ASCII se envia al PIC para poder sumarle
            cont++;                 //o restarle al contador 
        } else if (datos == 45){
            cont--;
        }
        Lcd_Set_Cursor(2,14);
        Lcd_Write_Number(cont);
        
        
        enviar(ent1);           //Se envian los datos a la computadora
        enviar(ent2);
        enviar(dec1);
        enviar(dec2);
        
        

    }
    return;
}




//Funcion de inicializacion de puertos
void init(void){
    OSCCONbits.IRCF = 0b110;
    OSCCONbits.SCS = 1;
    TRISB = 0;
    TRISD = 0;
    TRISC = 0;
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    ANSELH = 0;
    ANSEL = 0b00000011;
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    INTCON=0;
    INTCONbits.GIE = 1;
    INTCONbits.RBIF = 0;
}
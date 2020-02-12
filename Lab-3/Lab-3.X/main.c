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

//Protoripos de funciones
void init(void);

float pot1 = 0;
float pot2 = 0;
uint8_t adc = 0;
uint8_t ent1 = 0, ent2 =0, dec1 = 0, dec2 = 0;
float deci1 = 0, deci2 = 0;






//Vector de interrupcion

void __interrupt() ISR(void){
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
    if (PIR1bits.ADIF == 1){
        adc = 1;
//        if (ADCON0bits.CHS0 == 0){  //Si se utiliza el potenciometro 1 el valor del adc estara en su variable
//            pot1 = ADRESH;
//            ADCON0bits.GO_DONE=1;
//        }
//        if (ADCON0bits.CHS0 == 1){  //Si se utiliza el potenciometro 2 el valor del adc estara en su variable
//            pot2 = ADRESH;
//            ADCON0bits.GO_DONE=1;
//        }
        PIR1bits.ADIF = 0;

    } 
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

void main(void) {
//    INTCONbits.GIE = 1;
//    INTCONbits.PEIE = 1;
    init();
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("POT1");
    Lcd_Set_Cursor(1, 6);
    Lcd_Write_String("POT2");
    Lcd_Set_Cursor(1, 11);
    Lcd_Write_String("CONT");
    
    while(1){
        ADC1();
        if(adc == 1){
            pot1 = ADRESH;
            adc = 0;
            ADCON0bits.GO_DONE = 1;
        }
        pot1 = (pot1)* 5/255;
        ent1 = pot1;
        deci1 = (pot1 - ent1) * 100;
        dec1 = deci1;
        
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_Number(ent1);
        Lcd_Write_Char(".");
        Lcd_Write_Number(dec1);
        if(dec1 >= 10){//escribimos decimal según el caso
            Lcd_Write_Number(dec1);
        }else{
            Lcd_Write_String("0");
            Lcd_Write_Number(dec1);
        }
        __delay_ms(10);
               
        ADC2();
         if(adc == 1){
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
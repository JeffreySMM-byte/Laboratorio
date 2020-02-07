/*
 * File:   main1.c
 * Author: jeffr
 *
 * Created on January 31, 2020, 10:58 AM
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 8000000

#include <xc.h>
#include <stdint.h>
#include <pic16f887.h>
#include "ADC.h"
#include "TMR0.h"

//Prototipos de funciones y declaracion de variables
void init(void);
uint8_t i = 0; 
uint8_t contador = 0; 
uint8_t d1 = 0;
uint8_t d2 = 0;
uint8_t d = 0;
uint8_t adc = 0;

unsigned char const SEGMENT_MAP[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x6F, 0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47};




//Vector de interrupcion
void __interrupt() ISR(void){
    
    INTCONbits.GIE = 0;
    INTCONbits.RBIE = 0;
    INTCONbits.T0IE = 0;
    if(INTCONbits.RBIF == 1){

        if(PORTBbits.RB0 == 1){
            i++;
            PORTA = i;
        }

        if(PORTBbits.RB1 == 1){
            i--;
            PORTA = i;
        }


        INTCONbits.RBIF = 0;

    }


    if (PIR1bits.ADIF == 1){
        adc = 1;
        PIR1bits.ADIF = 0;

    } 
    if (INTCONbits.TMR0IF == 1) {
        INTCONbits.TMR0IF = 0;
        TMR0 = 4;
        if(contador == 0){
            contador = 1;
        } else {
            contador = 0;
        }
    }
    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.T0IE = 1;
}


//Programa principal

void main(void) {
    init();
    ADC();
    initTMR0();
    
    while(1){
        //PORTC = ADRESH;
        __delay_ms(10);
        ADCON0bits.GO_DONE = 1;
        if (adc == 1){
        d1 = ADRESH&0b00001111;
        d2 = (ADRESH&0b11110000)>>4;
        d = ADRESH;
        adc = 0;}
        if (i <= d){
            PORTDbits.RD2 = 1;
        }else{
            PORTDbits.RD2 = 0;
        }
                PORTDbits.RD1 = 1;
                PORTDbits.RD0 = 0;
                PORTC = SEGMENT_MAP[d1];
                __delay_ms(5);
                
                PORTDbits.RD1 = 0;
                PORTDbits.RD0 = 1;
                PORTC = SEGMENT_MAP[d2];
                __delay_ms(5);
            
    }
    
    return;
    
}



//Funcion de inicializacion de los puertos
void init(void){            
    TRISD = 0;
    TRISC = 0;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISA = 0;
    ANSELH = 0;
    ANSEL = 0;
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    INTCON=0;
    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    IOCBbits.IOCB2 = 1;
     
}



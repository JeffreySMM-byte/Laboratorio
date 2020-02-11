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

uint8_t pot1 = 0;
uint8_t pot2 = 0;





//Vector de interrupcion

void __interrupt() ISR(void){
    if (PIR1bits.ADIF == 1){
        if (ADCON0bits.CHS0 == 0){
            pot1 = ADRESH;
        }
        if (ADCON0bits.CHS0 == 1){
            pot2 = ADRESH;
        }
        PIR1bits.ADIF = 0;

    } 
}

void main(void) {
    init();
    interADC();
    Lcd_Init();
    while(1){
        ADC1();
        __delay_ms(10);
        ADC2();
        __delay_ms(10);
    }
    return;
}




//Funcion de inicializacion de puertos
void init(void){  
    TRISB = 0;
    TRISD = 0;
    TRISC = 0;
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 1;
    ANSELH = 0;
    ANSEL = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    INTCON=0;
    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;
}
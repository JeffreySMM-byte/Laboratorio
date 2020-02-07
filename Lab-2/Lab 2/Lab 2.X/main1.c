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
#define _XTAL_FREQ 4000000

#include <xc.h>
#include <stdint.h>



//Prototipos de funciones y declaracion de variables
void init(void);
uint8_t apachado = 0; 
uint8_t apachado2 = 0; 

void __interrupt() ISR(void){
//    if(INTCONbits.RBIF == 1){
    if (INTCONbits.RBIF==1){
        if(PORTBbits.RB0 == 1){
            INTCONbits.GIE=0;
            INTCONbits.RBIE=0;
            PORTAbits.RA1 = 1;
            INTCONbits.GIE=1;
            INTCONbits.RBIE=1;
            INTCONbits.RBIF=0;
        }
        if(PORTBbits.RB1 == 1){
            INTCONbits.GIE=0;
            INTCONbits.RBIE=0;
            PORTAbits.RA2 = 1;
            INTCONbits.GIE=1;
            INTCONbits.RBIE=1;
            INTCONbits.RBIF=0;  
        }
    }
    
//    if(PORTBbits.RB0 == 1 && apachado ==0){
//        INTCONbits.GIE = 0;
//        INTCONbits.RBIE = 0;
//        apachado = 1;
//        PORTA++;
//        INTCONbits.GIE = 1;
//        INTCONbits.RBIE = 1;
//        INTCONbits.RBIF = 0;
//    }
//    if(PORTBbits.RB0 == 0){
//        apachado = 0;
//    }
//    
//     if(PORTBbits.RB1 == 1 && apachado2 ==0){
//        INTCONbits.GIE = 0;
//        INTCONbits.RBIE = 0;
//        apachado2 = 1;
//        PORTA--;
//        INTCONbits.GIE = 1;
//        INTCONbits.RBIE = 1;
//        INTCONbits.RBIF = 0;
//    }
//    if(PORTBbits.RB1 == 0){
//        apachado2 = 0;
//    }
//    
//}
} 


//Programa principal

void main(void) {
    init();
   
    
    return;
    
}



//Funcion de inicializacion de los puertos
void init(void){            
    TRISD = 0;
    TRISC = 0;
    TRISEbits.TRISE0 = 1;
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
}

/*
 * File:   main2.c
 * Author: jeffr
 *
 * Created on January 27, 2020, 9:24 PM
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



void init(void);
void delay_ms(unsigned int dms);
void leds(void);
void leds2(void);
void p1(void);
char bandera = 0;
char led1 = 0;
char led2 = 0;
char apachado = 0;
char antiguo = 0;
unsigned char const SEGMENT_MAP[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x6F};




void main(void) {
    init();
     while(1){
    if(PORTDbits.RD0 == 1){    //Se revisa si el boton de inicio se presiono.
        PORTDbits.RD3 = 1;
        PORTDbits.RD4 = 0;
        PORTDbits.RD5 = 0;
        PORTC = (SEGMENT_MAP[3]);
        __delay_ms(1000);
        
        PORTDbits.RD3 = 0;
        PORTDbits.RD4 = 1;
        PORTDbits.RD5 = 0;
        PORTC = (SEGMENT_MAP[2]);
        __delay_ms(1000);
        
        PORTDbits.RD3 = 0;
        PORTDbits.RD4 = 0;
        PORTDbits.RD5 = 1;
        PORTC = (SEGMENT_MAP[1]);
        __delay_ms(1000);
        
        PORTDbits.RD3 = 1;
        PORTDbits.RD4 = 1;
        PORTDbits.RD5 = 1;
        PORTC = (SEGMENT_MAP[0]);
        bandera = 1;
        __delay_ms(1000);
        while(bandera == 1){
           if (PORTDbits.RD1 == 1 && apachado ==0){ 
             apachado = 1;  
             leds();
             __delay_ms(100);
//             while(PORTDbits.RD1 == 1){
//                 __delay_ms(100);
//             }
           } //else 
           if (PORTDbits.RD2 == 1 && antiguo == 0 ){
               antiguo = 1;
               leds2();
                __delay_ms(100);
//               while(PORTDbits.RD2 == 1){
//                   __delay_ms(100);
//               }
            }
           if(PORTDbits.RD1 == 0){
               apachado = 0;
               
           } 
           if(PORTDbits.RD2 == 0){
               antiguo = 0;
           }
           if(PORTDbits.RD6 == 1){
                   PORTC = 0x06; //display 7 segmentos
                   bandera = 0;
                } else if(PORTDbits.RD7 == 1){
                   PORTC = 0x5B;    //display 7 segmentos
                   bandera = 0;
                }
        }
        
            
    }
     }
    return;
}




void init(void){            //Se establece que puertos son entradas y salidas.
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISE = 0;
    TRISDbits.TRISD0 = 1;
    TRISDbits.TRISD1 = 1;
    TRISDbits.TRISD2 = 1;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD7 = 0;
    ANSELH = 0;
    ANSEL = 0;
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
}


//void delay_ms(unsigned int dms){
//    for(int i=0; i<dms;i++){
//        for(int j=0; j<255; j++){
//    }
//}
//}





void leds(void){
    led1++;
      if (led1>0 ){
          switch(led1){
        case 1:
            PORTAbits.RA0 =1 ;
            break;
        case 2:
            PORTAbits.RA1 = 1;
            break;
        case 3:
            PORTAbits.RA2 = 1;
            break;
        case 4:
            PORTAbits.RA3 = 1;
            break;
        case 5: 
            PORTAbits.RA4 = 1;
            break; 
        case 6: 
            PORTAbits.RA5 = 1;
            break; 
        case 7: 
            PORTEbits.RE0 = 1;
            break;
        case 8: 
            PORTEbits.RE1 = 1;
            PORTDbits.RD6 = 1;
            break;
            } 
      }
}
void leds2(void){
    led2++;
      if (led2>0 ){
          switch(led2){
        case 1:
            PORTBbits.RB0 = 1;
            break;
        case 2:
            PORTBbits.RB1 = 1;
            break;
        case 3:
            PORTBbits.RB2 = 1;
            break;
        case 4:
            PORTBbits.RB3 = 1;
            break;
        case 5: 
            PORTBbits.RB4 = 1;
            break; 
        case 6: 
            PORTBbits.RB5 = 1;
            break; 
        case 7: 
            PORTBbits.RB6 = 1;
            break;
        case 8: 
            PORTBbits.RB7 = 1;
            PORTDbits.RD7 = 1;
            break;
            } 
      }
}

//void leds(void){
//    if(apachado == 1){
//        if (antiguo == 1){
//            
//        } else {
//            led1++;
//            switch(led1){
//        case 1:
//            PORTAbits.RA0 =1 ;
//            break;
//        case 2:
//            PORTAbits.RA1 = 1;
//            break;
//        case 3:
//            PORTAbits.RA2 = 1;
//            break;
//        case 4:
//            PORTAbits.RA3 = 1;
//            break;
//        case 5: 
//            PORTAbits.RA4 = 1;
//            break; 
//        case 6: 
//            PORTAbits.RA5 = 1;
//            break; 
//        case 7: 
//            PORTAbits.RA6 = 1;
//            break;
//        case 8: 
//            PORTAbits.RA7 = 1;
//            break;
//        case 9: 
//            PORTDbits.RD6 = 1;
//            break;
//   
//    }
//            antiguo = 1;
//            
//        }
//    }else {
//        antiguo = 0;
//    }
//}


// void p1(void){
//     switch(led1){
//        case 1:
//            PORTAbits.RA0 =1 ;
//            break;
//        case 2:
//            PORTAbits.RA1 = 1;
//            break;
//        case 3:
//            PORTAbits.RA2 = 1;
//            break;
//        case 4:
//            PORTAbits.RA3 = 1;
//            break;
//        case 5: 
//            PORTAbits.RA4 = 1;
//            break; 
//        case 6: 
//            PORTAbits.RA5 = 1;
//            break; 
//        case 7: 
//            PORTAbits.RA6 = 1;
//            break;
//        case 8: 
//            PORTAbits.RA7 = 1;
//            break;
//        case 9: 
//            PORTDbits.RD6 = 1;
//            break;
//   
//    } 
//  }
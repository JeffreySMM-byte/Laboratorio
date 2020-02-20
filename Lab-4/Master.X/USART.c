#include <stdint.h>
#include <pic16f887.h>
#include <stdio.h>
#include <stdlib.h>
#include "USART.h"

void serial (void){         //Funcion de inicializacion de UART
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    TRISC = 0x80;
    PIE1bits.RCIE = 0;
    TXSTA = 0b00100110;
    RCSTA = 0b10010000;
    BAUDCTLbits.BRG16 = 1; //BaudrateHigh
    SPBRG = 103;
}



void enviar (int dat){              //Funcion de envio de datos
    
//    if(TXSTAbits.TRMT == 0){
//        
//    } else { 
//        TXREG = dat;
//    }
    while (TXSTAbits.TRMT == 0){
    }
    TXREG = dat;
}


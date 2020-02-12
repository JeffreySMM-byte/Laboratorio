#include <stdint.h>
#include <pic16f887.h>
#include <stdio.h>
#include <stdlib.h>
#include "USART.h"

void serial (void){
    TRISC = 0x80;
    PIE1bits.RCIE = 0;
    TXSTA = 0b00100110;
    RCSTA = 0b10010000;
    SPBRG = 103;
}



void enviar (int dat){
    
//    if(TXSTAbits.TRMT == 0){
//        
//    } else { 
//        TXREG = dat;
//    }
    while (TXSTAbits.TRMT == 0){
    }
    TXREG = dat;
}

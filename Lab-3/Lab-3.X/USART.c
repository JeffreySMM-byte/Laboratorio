#include <stdint.h>
#include <pic16f887.h>
#include <stdio.h>
#include <stdlib.h>
#include "USART.h"

void serial (void){         //Funcion de inicializacion de UART
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 0;
    PIE1bits.RCIE = 1;
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

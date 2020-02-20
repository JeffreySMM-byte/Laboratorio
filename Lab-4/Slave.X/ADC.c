#include <stdint.h>
#include <pic16f887.h>
#include "ADC.h"

void ADC1(void){                    //Funcion de inicializacion del ADC para el puerto A0
//while(ADCON0bits.GO_DONE == 1);

    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    ADCON0bits.ADCS=01;
    ADCON0bits.CHS0=0;
    ADCON0bits.CHS1=0;
    ADCON0bits.CHS2=0;
    ADCON0bits.CHS3=0; //Se usa el AN0
    ADCON0bits.ADON=1;
    ADCON1bits.ADFM=0;
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    PIE1bits.ADIE=1;
    PIR1bits.ADIF=0;



    ADCON0bits.GO_DONE=1;

}
void ADC2(void){                    //Funcion de inicializacion del ADC para el puerto A1
//while(ADCON0bits.GO_DONE == 1);
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    ADCON0bits.ADCS=01;
    ADCON0bits.CHS0=1;
    ADCON0bits.CHS1=0;
    ADCON0bits.CHS2=0;
    ADCON0bits.CHS3=0; //Se usa el AN1
    ADCON0bits.ADON=1;
    ADCON1bits.ADFM=0;
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    PIE1bits.ADIE=1;
    PIR1bits.ADIF=0;

    ADCON0bits.GO_DONE=1;

}



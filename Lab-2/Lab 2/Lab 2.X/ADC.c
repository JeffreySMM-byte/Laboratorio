#include <stdint.h>
#include <pic16f887.h>
#include "ADC.h"

void ADC(void){
PIE1bits.ADIE=1;
PIR1bits.ADIF=1;
ADCON0bits.ADCS=01;
ADCON0bits.CHS0=0;
ADCON0bits.CHS1=0;
ADCON0bits.CHS2=0;
ADCON0bits.CHS3=1;
ADCON0bits.GO_nDONE=0;
ADCON0bits.ADON=1;
ADCON1bits.ADFM=0;
ADCON1bits.VCFG0=0;
ADCON1bits.VCFG1=0;
}

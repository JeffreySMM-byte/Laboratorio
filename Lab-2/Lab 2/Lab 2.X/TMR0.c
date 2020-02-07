#include <stdint.h>
#include <pic16f887.h>
#include "TMR0.h"

void initTMR0(void) {
    OPTION_REG = 0x81; // Configuración para tener un desborde 
    TMR0 = 4; // de 0.5 mS    
    INTCONbits.T0IE = 1;
}
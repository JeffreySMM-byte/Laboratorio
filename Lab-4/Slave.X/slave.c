//*****************************************************************************
/*
 * File:   main.c
 * Author: Pablo
 * Ejemplo de implementaci�n de la comunicaci�n SPI 
 * C�digo Esclavo
 * Created on 10 de febrero de 2020, 03:32 PM
 */
//*****************************************************************************
//*****************************************************************************
// Palabra de configuraci�n
//*****************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
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

//*****************************************************************************
// Definici�n e importaci�n de librer�as
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "SPI.h"
#include "ADC.h"
//*****************************************************************************
// Definici�n de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000
//*****************************************************************************
// Definici�n de funciones para que se puedan colocar despu�s del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
float pot1 = 0;
float pot2 = 0;
uint8_t adc = 0, adc1 = 0, adc2 = 0, valor = 0;
uint8_t ent1 = 0, ent2 =0, dec1 = 0, dec2 = 0, datos = 0, cont = 0;
float deci1 = 0, deci2 = 0;
//*****************************************************************************
// C�digo de Interrupci�n 
//*****************************************************************************
void __interrupt() isr(void){
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
    
    if (PIR1bits.ADIF == 1){
        adc = 1;                //Se levanta un bandera cuando el ADC entre a la interrupcion
        PIR1bits.ADIF = 0;

    }
    
   if(SSPIF == 1){
        valor = spiRead();
        if(valor == 1){
            spiWrite(adc1);
        }
        if(valor == 2){
            spiWrite(adc2);
        }
        SSPIF = 0;
    }
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}
//*****************************************************************************
// C�digo Principal
//*****************************************************************************
void main(void) {
    setup();
    
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    while(1){
        ADC1();
        if(adc == 1){           // de ADRESH a una variable 
            adc1 = ADRESH;
            adc = 0;
            PORTD = adc1;
            ADCON0bits.GO_DONE = 1;
        }
        
        ADC2();
        if(adc == 1){           // de ADRESH a una variable 
            adc2 = ADRESH;
            adc = 0;
            PORTB = adc2;
            ADCON0bits.GO_DONE = 1;
        }
        
  
        //PORTD = pot1;
        
        __delay_ms(10);

    }
    return;
}
//*****************************************************************************
// Funci�n de Inicializaci�n
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    
    TRISB = 0;
    TRISD = 0;
    
    PORTB = 0;
    PORTD = 0;
    
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupci�n MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupci�n MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
   
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

}
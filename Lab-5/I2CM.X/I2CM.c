/*
 * File:   main.c
 * Author: Pablo
 * Ejemplo de uso de I2C Master
 * Created on 17 de febrero de 2020, 10:32 AM
 */
//*****************************************************************************
// Palabra de configuración
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
// Definición e importación de librerías
//*****************************************************************************
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include <xc.h>
#include"LCD8bits.h"
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000

//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
float adc1 = 0, deci1 = 0;
uint8_t pvtoelquelolea = 0, ent1 = 0, dec1 = 0, segundos = 0, minutos = 0;


void setup(void);
int  BCD(int to_convert) // Función para convertir BCD a decimal (el RTC trabaja con BCD)
{
   return (to_convert >> 4) * 10 + (to_convert & 0x0F); 
}

//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("ADC");
    Lcd_Set_Cursor(1, 6);
    Lcd_Write_String("CONT");
    Lcd_Set_Cursor(1, 11);
    Lcd_Write_String("TIME");
    while(1){
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        adc1 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(10);
       
        I2C_Master_Start();
        I2C_Master_Write(0x61);
        pvtoelquelolea = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(10);
        
        
        adc1 = (adc1)* 5/255;       //Se realiza un mapeo para los valores del ADRESH y se separa 
        ent1 = adc1;                //en dos enteros para poder desplegarlos como la parte entera y decimal del voltaje
        deci1 = (adc1 - ent1) * 100;
        dec1 = deci1;
        
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_Number(ent1);
        Lcd_Write_Char(".");
        Lcd_Write_Number(dec1);
        
        

        
        
        if(pvtoelquelolea < 10){ 
            Lcd_Set_Cursor(2,7);
            Lcd_Write_String("0");
            Lcd_Write_Number(pvtoelquelolea);
        }else{
            Lcd_Set_Cursor(2,7);
            Lcd_Write_Number(pvtoelquelolea);
        }
        
//        if(pvtoelquelolea < 0){
//            Lcd_Set_Cursor(2, 7);
//            Lcd_Write_String("16");
//            Lcd_Write_Number(pvtoelquelolea);
//        } else if (pvtoelquelolea>16){
//            Lcd_Set_Cursor(2, 7);
//            Lcd_Write_String("0");
//            Lcd_Write_Number(pvtoelquelolea);
//            
//        }
        
       //Lectura del RTC
       I2C_Master_Start();       
       I2C_Master_Write(0xD0); 
       I2C_Master_Write(0);    
       I2C_Master_Stop();
       
 
       I2C_Master_Start();
       I2C_Master_Write(0xD1);                              // Initialize data read
       segundos = BCD(I2C_Master_Read(0));                 // Lectura de segundos
       I2C_Master_Stop(); 

       I2C_Master_Start();
       I2C_Master_Write(0xD1);                              // Initialize data read
       minutos = BCD(I2C_Master_Read(0));                 // Lectura de minutos
       I2C_Master_Stop();  


       I2C_Master_Start();
       I2C_Master_Write(0xD1);                              // Initialize data read
       I2C_Master_Read(0);                                 // Lectura de fin de transmisión
       I2C_Master_Stop();
        
        
       Lcd_Set_Cursor(2, 12);
       Lcd_Write_Number(minutos);
       Lcd_Write_Char(':');
       Lcd_Write_Number(segundos);
       
       
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    I2C_Master_Init(100000);        // Inicializar Comuncación I2C
}
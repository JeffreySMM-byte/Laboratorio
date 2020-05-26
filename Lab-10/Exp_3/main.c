/**
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"



uint8_t Pin=14;
uint8_t led = 0;
uint8_t apachado = 0;
uint8_t d;
uint8_t apachado2 = 0;
char* colord;


void led1(void);
void send (char* word);
void init (void);

int main(void){

    //Clock settings
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //Peripheral GPIOF
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    //Output pins
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    //Input pin
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);

    //Button config (SW1 & SW2)
    HWREG (GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0X1;
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);


    //UART settings
       SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
       GPIOPinConfigure( GPIO_PB0_U1RX );
       GPIOPinConfigure( GPIO_PB1_U1TX );
       GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1);
       UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,
               (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    init();


    while(1){

        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0 && apachado2 == 0){
                    apachado2 = 1;
                    send("AT+CIPSTART=");
                    UARTCharPut(UART1_BASE, '"');
                    send("TCP");
                    UARTCharPut(UART1_BASE, '"');
                    UARTCharPut(UART1_BASE, ',');
                    UARTCharPut(UART1_BASE, '"');
                    send("192.168.0.14");
                    UARTCharPut(UART1_BASE, '"');
                    send(",80\r\n");
                    SysCtlDelay(300000);
                    send("AT+CIPSEND=175\r\n");
                    SysCtlDelay(300000);
                    send(colord);
                    SysCtlDelay(300000);
                    send("\nAT+CIPCLOSE\n");


                }
                if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) != 0){
                    apachado2 = 0;
                    SysCtlDelay(150);

                }

        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0 && apachado == 0){
            apachado = 1;
            //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            led1();
            SysCtlDelay(150);

        }
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) != 0){
            //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            apachado = 0;
            //led1();
            SysCtlDelay(150);

        }

    }


}


void init (void){
    send("AT\r\n");
    SysCtlDelay(300000);
    send("AT+CWMODE=1\r\n");
    SysCtlDelay(300000);
    send("AT+CWJAP=");
    UARTCharPut(UART1_BASE, '"');
    send("ARRIS-EFD2");
    UARTCharPut(UART1_BASE, '"');
    UARTCharPut(UART1_BASE, ',');
    UARTCharPut(UART1_BASE, '"');
    send("2PM7H7602357");
    UARTCharPut(UART1_BASE, '"');
    send("\r\n");
    SysCtlDelay(300000);

}


void send (char* word){
    for (d = 0; d<strlen(word); d++){
        UARTCharPut(UART1_BASE, word[d]);
    }
 }



void led1(void){
    led++;
    if(led>0){
        switch(led){
        case 1:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
            colord = "POST /index.php HTTP/1.0\r\nHost:  192.168.0.14\r\nAccept: */*\r\nContent-Length: 38\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ncarnet=17323&id_color=1&color=Azul    ";
            break;
        case 2:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            colord = "POST /index.php HTTP/1.0\r\nHost:  192.168.0.14\r\nAccept: */*\r\nContent-Length: 38\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ncarnet=17323&id_color=2&color=Verde   ";
            break;
        case 3:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            colord = "POST /index.php HTTP/1.0\r\nHost:  192.168.0.14\r\nAccept: */*\r\nContent-Length: 38\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ncarnet=17323&id_color=3&color=Turquesa";
            break;
        case 4:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
            colord = "POST /index.php HTTP/1.0\r\nHost:  192.168.0.14\r\nAccept: */*\r\nContent-Length: 38\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ncarnet=17323&id_color=4&color=Rojo    ";
            break;
        case 5:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
            colord = "POST /index.php HTTP/1.0\r\nHost:  192.168.0.14\r\nAccept: */*\r\nContent-Length: 38\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ncarnet=17323&id_color=5&color=Violeta ";
            break;
        case 6:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
            colord = "POST /index.php HTTP/1.0\r\nHost:  192.168.0.14\r\nAccept: */*\r\nContent-Length: 38\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ncarnet=17323&id_color=6&color=Amarillo";
            break;
        case 7:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
            colord = "POST /index.php HTTP/1.0\r\nHost:  192.168.0.14\r\nAccept: */*\r\nContent-Length: 38\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ncarnet=17323&id_color=7&color=Blanco  ";
            break;
        case 8:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
            colord = "POST /index.php HTTP/1.0\r\nHost:  192.168.0.14\r\nAccept: */*\r\nContent-Length: 38\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ncarnet=17323&id_color=0&color=Negro   ";
            break;

        }
        if(led>8){
            led = 0;
        }
    }



}






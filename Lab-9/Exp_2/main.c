/**
 * main.c
 */


#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"

uint8_t pin=14;
uint32_t period, estado;
uint32_t r = 0, g = 0, b = 0, c = 0;


int main(void){

    //Clock settings
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //Peripheral GPIOF and GPIOA
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //Output pins
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    //Timer0 settings
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    //GPIO toggle 1Hz and 50% duty cicle
    period = (SysCtlClockGet()/1)/2;
    TimerLoadSet(TIMER0_BASE, TIMER_A, period-1);

    //Interrupt enable Timer0
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();

    //Timer enable
    TimerEnable(TIMER0_BASE, TIMER_A);

    //UART settings
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    //Interrupt enable UART
    IntMasterEnable();
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);




   while(1){

    }
}

    void Timer0IntHandler(void){
        TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

        if (b == 1){
            if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2)){
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
            }else{
               GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, pin);
            }
        }
        if(r == 1){
            if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1)){
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
            }else{
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, pin);
            }
        }
        if(g == 1){
            if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3)){
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
            }else{
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, pin);
            }
        }

    }

    void UARTIntHandler(void)
    {

        estado = UARTIntStatus(UART0_BASE, true);

        UARTIntClear(UART0_BASE, estado);

        while(UARTCharsAvail(UART0_BASE)) //loop while there are chars
        {
            c = UARTCharGet(UART0_BASE);

            if (c == 66 && b == 0){
                b = 1;
            }else if (c == 66 && b == 1){
                b = 0;
            }

            if(c == 82 && r == 0){
                r = 1;
            }else if(c == 82 && r == 1){
                r = 0;
            }

            if(c == 71 && g == 0){
                g = 1;
            }else if (c == 71 && g == 1){
                g = 0;
            }
        }
    }




/**
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"

uint8_t ui8PinData=14;

int main(void){

    //Clock settings
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //Peripheral GPIOF
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //Output pins
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    //Input pin
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    //Button config (SW1)
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    while(1){

        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0){
            //Si lee un cambio en el boton SW1 comienza la secuencia del semaforo encendiendo el LED verde
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, ui8PinData);
            SysCtlDelay(20000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, ui8PinData);
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, ui8PinData);
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, ui8PinData);
            SysCtlDelay(2000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            SysCtlDelay(2000000);

            //Al terminar la secuencia del LED verde comienza la secuencia del LED amarillo
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, ui8PinData);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ui8PinData);
            SysCtlDelay(20000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
            SysCtlDelay(2000000);

            //Al terminar la secuencia del LED amarillo comienza la secuencia del LED rojo
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ui8PinData);
            SysCtlDelay(20000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);



        }
    }



}

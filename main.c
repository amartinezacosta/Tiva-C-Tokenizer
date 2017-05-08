#include <stdint.h>
#include <stdbool.h>
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "utils/uartstdio.h"
#include "tokenizer.h"

#define USER_INPUT_BUFFER   64
#define DELIMITERS          "AXYZ"

void
InitConsole(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTStdioConfig(0, 115200, 16000000);
}


int main(void) {
	
    InitConsole();

    char Buffer[USER_INPUT_BUFFER];
	char Token_Buffer[MAX_TOKENS][MAX_TOKEN_SIZE];
	uint8_t tokens_found;

    while(1){
	    UARTgets(Buffer, USER_INPUT_BUFFER);
	    tokens_found = TokenizeString(Buffer, DELIMITERS, Token_Buffer);

	    if(tokens_found == 0){
	        UARTprintf("No tokens found/buffer overflow in string: %s\n", Buffer);
	    }

	    uint8_t i;
	    for(i = 0; i < tokens_found; i++){
	        UARTprintf("%s\n", Token_Buffer[i]);
	    }

	}

}

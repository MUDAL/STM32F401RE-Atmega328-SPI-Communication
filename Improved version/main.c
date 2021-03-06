#include "stm32f4xx.h"                  // Device header
#include <stdbool.h>
#include "clock.h"
#include "gpio.h"
#include "spi2.h"
#include "button.h"

//Simple program to interface STM32 with Atmega328..
//via SPI communication.

//When the onboard button on the stm32 nucleo board is pressed,
//a character is sent to the Atmega328 via SPI. The character received by
//the Atmega328 can be viewed on the serial monitor of the Arduino IDE using UART.

//Connections:
//Onboard button --> PC13
//Slave select pin --> PB12 (NSS software management)
//SCK pin -->  PB13
//MISO pin --> PB14
//MOSI pin --> PB15

int main(void)
{
	Clocks_Init();
	GPIO_Init();
	SPI2_Init();
	SPI2_Enable();
	SPI2_SlaveSelect(GPIOB,GPIO_PIN_12);
	
	while(1){
		
		if (ReadButton(GPIOC,GPIO_PIN_13))
		{
			SPI2_SendOneByte('Q');
		}
		
	}
}


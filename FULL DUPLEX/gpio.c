#include "stm32f4xx.h"                  // Device header
#include "gpio.h"

void GPIO_Init(void)
{
	//alternate function mode for PB13,PB14,PB15 and output mode for PB12
	GPIOB->MODER |= (GPIO_MODER_MODE12_0 | GPIO_MODER_MODER13_1 | 
									GPIO_MODER_MODER14_1 | GPIO_MODER_MODER15_1); 
	//Select SPI2 functionality for PB13(SCK),PB14(MISO),PB15(MOSI)
	GPIOB->AFR[1] |= (GPIO_AFRH_AFSEL13_0 | GPIO_AFRH_AFSEL13_2 |
										GPIO_AFRH_AFSEL14_0 | GPIO_AFRH_AFSEL14_2 |
										GPIO_AFRH_AFSEL15_0 | GPIO_AFRH_AFSEL15_2 );
	
	//Enable pullup resistor for PC13
	GPIOC->PUPDR |= GPIO_PUPDR_PUPD13_0; 
}

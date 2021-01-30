#include "stm32f4xx.h"                  // Device header
#include "clock.h"

void Clocks_Init(void)
{
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN); //Enable GPIO B and C  clock
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;//enable SPI2 clock
}

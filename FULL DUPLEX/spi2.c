#include "stm32f4xx.h"                  // Device header
#include "spi2.h"

void SPI2_Init(void)
{
	//serial clock baud rate = 4 hence SPI clock output = 16MHz / 4 = 4MHz
	//enable software slave management
	//enable internal slave select
	//enable master mode
	SPI2->CR1 |= SPI_CR1_BR_0 | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_MSTR;
}

void SPI2_SendOneByte(char data)
{
	while ((SPI2->SR & SPI_SR_TXE) != SPI_SR_TXE); //wait for transmit buffer to be empty
	SPI2->DR = data;
}

char SPI2_ReceiveOneByte(void)
{
	while ((SPI2->SR & SPI_SR_RXNE) != SPI_SR_RXNE); //wait for receive buffer to contain data
	return SPI2->DR;
}

void SPI2_Enable(void)
{
	SPI2->CR1 |= SPI_CR1_SPE;
}	

void SPI2_SlaveSelect(GPIO_TypeDef* nssGpioPort, uint8_t nssGpioPin)
{
	nssGpioPort->ODR &= ~(1<<nssGpioPin);
}	

void SPI2_SlaveDeselect(GPIO_TypeDef* nssGpioPort, uint8_t nssGpioPin)
{
	nssGpioPort->ODR |= (1<<nssGpioPin);
}

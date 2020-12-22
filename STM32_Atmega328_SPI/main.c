#include "stm32f4xx.h"                  // Device header
#include <stdbool.h>

//Simple program to interface STM32 with Atmega328..
//via SPI communication.

//When the onboard button on the stm32 nucleo board is pressed,
//a character is sent to the Atmega328 via SPI. The character received by
//the Atmega328 can be viewed on the serial monitor of the Arduino IDE using UART.

//Connections:
//Onboard button --> PC13
//Slave select pin --> PB12
//SCK pin --> PB13
//MISO pin --> PB14
//MOSI pin --> PB15

typedef struct{
	bool pressed;
	bool prevPressed;
}button_t;

button_t button = {false,false};

void ConfigureClocks(void){
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN); //Enable GPIO B and C  clock
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; //set APB1 prescaler to 2 i.e. APB1 clock = 16MHz / 2 = 8MHz
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;//enable SPI2 clock
}

void ConfigureSPI2(void){
	//By default, serial clock baud rate = 2 hence SPI clock output = 8MHz / 2 = 4MHz
	SPI2->CR2 |= SPI_CR2_SSOE;//NSS pin in output mode
	SPI2->CR1 |= SPI_CR1_MSTR; //master mode
}

void ConfigureGPIOB(void){
	GPIOC->PUPDR |= GPIO_PUPDR_PUPD13_0; //Enable pullup resistor for PC13
	//alternate function mode for PB12,PB13,PB14,PB15
	GPIOB->MODER |= (GPIO_MODER_MODER12_1 | GPIO_MODER_MODER13_1 | 
									GPIO_MODER_MODER14_1 | GPIO_MODER_MODER15_1); 
	//Select SPI2 functionality for PB12(NSS),PB13(SCK),PB14(MISO),PB15(MOSI)
	GPIOB->AFR[1] |= (GPIO_AFRH_AFSEL12_0 | GPIO_AFRH_AFSEL12_2 |
										GPIO_AFRH_AFSEL13_0 | GPIO_AFRH_AFSEL13_2 |
										GPIO_AFRH_AFSEL14_0 | GPIO_AFRH_AFSEL14_2 |
										GPIO_AFRH_AFSEL15_0 | GPIO_AFRH_AFSEL15_2 );
}

void SPI2_SendOneByte(char data){
	while ((SPI2->SR & SPI_SR_TXE) != SPI_SR_TXE){} //wait for transmit buffer to be empty
	SPI2->DR = data;
}

int main(void){
	ConfigureClocks();
	ConfigureGPIOB();
	ConfigureSPI2();
	SPI2->CR1 |= SPI_CR1_SPE;//Enable SPI2
	while(1){
		button.pressed = !(GPIOC->IDR & GPIO_IDR_ID13);
		
		if (button.pressed && !button.prevPressed){
			SPI2_SendOneByte('Z');
			button.prevPressed = true;
		}
		else if (!button.pressed && button.prevPressed){
			button.prevPressed = false;
		}
	}
}


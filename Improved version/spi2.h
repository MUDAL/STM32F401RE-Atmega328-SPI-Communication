#ifndef _SPI2_H
#define _SPI2_H

extern void SPI2_Init(void);
extern void SPI2_SendOneByte(char data);
extern void SPI2_Enable(void);
extern void SPI2_SlaveSelect(GPIO_TypeDef* nssGpioPort, uint8_t nssGpioPin);
extern void SPI2_SlaveDeselect(GPIO_TypeDef* nssGpioPort, uint8_t nssGpioPin);

#endif //_SPI2_H

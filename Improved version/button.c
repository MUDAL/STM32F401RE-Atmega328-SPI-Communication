#include "stm32f4xx.h"                  // Device header
#include <stdbool.h>
#include "button.h"

bool ReadButton(GPIO_TypeDef* gpioPort, uint8_t gpioPin)
{
	static bool pressed; 
	static bool prevPressed;
	
	pressed = !(gpioPort->IDR & (1<<gpioPin));
	
	if (pressed && !prevPressed)
	{
		prevPressed = true;
		return true;
	}
	
	else if (!pressed && prevPressed)
	{
		prevPressed = false;
		return false;
	}
	
	return false;
}

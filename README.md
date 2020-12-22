# STM32F401RE-Atmega328-SPI-Communication
Simple SPI communication between the STM32F401RE and Atmega328 microcontrollers

When the onboard button on the nucleo board is pressed, a character is sent to the Atmega328 via SPI.
The character received by the Atmega328 can be displayed on a serial terminal via UART (in this example, the Arduino serial monitor is used).

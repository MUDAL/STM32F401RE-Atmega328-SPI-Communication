/*
 * Simple code to receive data from and transmit data to the stm32f401re nucleo board via
 * SPI communication.
 * 
 * Whenever the SPI receive buffer contains data, an interrupt is raised and the
 * data is read.
 * 
 * CONNECTIONS:
 *  PIN     |   ATMEGA     |  ARDUINO
 * 1.)SS    |     PB2      |  digital pin 10
 * 2.)SCK   |     PB5      |  digital pin 13
 * 3.)MISO  |     PB4      |  digital pin 12
 * 4.)MOSI  |     PB3      |  digital pin 11
*/

volatile char receivedData;

void setup()
{
  //Configuration code
  cli();
  DDRB |= (1<<DDB4);//Configure MISO pin(PB4) as output
  SPCR = (1<<SPIE)|(1<<SPE);//Enable SPI interrupt, Enable SPI
  sei();
}

void loop()
{
  
}

ISR(SPI_STC_vect)
{
  receivedData = SPDR;
  if (receivedData == 'r')
  {
    SPDR = 'M';
  }
}

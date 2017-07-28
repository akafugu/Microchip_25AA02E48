#include "Microchip_25AA02E48.h"

#define READ_instruction 0b00000011     // 25AA02A's read command
#define WRITE_instruction 0b00000010    // 25AA02A's write command
#define READ_STATUS_instruction  0b00000101   
#define WRITE_STATUS_instruction 0b00000001
#define WREN 6

Microchip_25AA02E48::Microchip_25AA02E48(uint8_t cs) {
	_cs = cs;
	pinMode(_cs, OUTPUT);
	digitalWrite(_cs, HIGH);
}

uint8_t Microchip_25AA02E48::readStatus() {
  uint8_t result = 0;   // result to return
  
  // take the chip select low to select the device:
  digitalWrite(_cs, LOW);
  
  SPI.transfer(READ_STATUS_instruction);
  result = SPI.transfer(0x00);
  digitalWrite(_cs, HIGH);
  
  return result;
}


uint8_t Microchip_25AA02E48::readRegister(uint8_t addr) {
  uint8_t result = 0;   // result to return
  // take the chip select low to select the device:
  digitalWrite(_cs, LOW);
  SPI.transfer(READ_instruction);
  // send the device the register you want to read:
  SPI.transfer(addr);
  // send a value of 0 to read the first byte returned:
  result = SPI.transfer(0x00);
  
  // take the chip select high to de-select:
  digitalWrite(_cs, HIGH);
  
  // return the result:
  return result;
}

uint8_t Microchip_25AA02E48::readRegister(uint8_t addr, uint8_t *buffer, int len) {
  if(buffer == 0)
    return 1;
  int index = 0;
  uint8_t result = 0;   // result to return
  // take the chip select low to select the device:
  digitalWrite(_cs, LOW);
  SPI.transfer(READ_instruction);
  // send the device the register you want to read:
  SPI.transfer(addr);
  while(len > index)
  {
    result = SPI.transfer(0x00);
    buffer[index] = result;
    index++;
  }
  
  digitalWrite(_cs, HIGH);
  
  // return the result:
  return 0;
}


void Microchip_25AA02E48::getEUI48(uint8_t *buffer) {
	// take the chip select low to select the device:
	digitalWrite(_cs, LOW);
	SPI.transfer(READ_instruction);
	// send the device the register you want to read:
	SPI.transfer(0xFA);
	for(uint8_t i = 0; i < 6; i++)
	{
		buffer[i] = SPI.transfer(0x00);
	}
	
	digitalWrite(_cs, HIGH);
}

void Microchip_25AA02E48::getEUI64(uint8_t *buffer) {
	// take the chip select low to select the device:
	digitalWrite(_cs, LOW);
	SPI.transfer(READ_instruction);
	// send the device the register you want to read:
	SPI.transfer(0xFA);
	for(uint8_t i = 0; i < 8; i++)
	{
		if(i == 3)
			buffer[i] = 0xFF;
		else if(i == 4)
			buffer[i] = 0xFE;
		else
			buffer[i] = SPI.transfer(0x00);
	}
	
	digitalWrite(_cs, HIGH);
}

void Microchip_25AA02E48::writeRegister(uint8_t addr, uint8_t value) {
  // take the chip select low to select the device:
  digitalWrite(_cs, LOW);
  SPI.transfer(WREN);
  digitalWrite(_cs, HIGH);
  
  digitalWrite(_cs, LOW);

  SPI.transfer(WRITE_instruction);
  SPI.transfer(addr); //Send register location
  SPI.transfer(value);  //Send value to record into register

  // take the chip select high to de-select:
  digitalWrite(_cs, HIGH);
}


void Microchip_25AA02E48::writeRegister(uint8_t addr, uint8_t *buffer, int len) {
  int index = 0;
  while (len > index) 
  {
    // Check which page we are writing to
    uint8_t page = (addr + index) >> 4;

    // take the chip select low to select the device:
    digitalWrite(_cs, LOW);
    SPI.transfer(WREN);
    digitalWrite(_cs, HIGH);

    digitalWrite(_cs, LOW);

    SPI.transfer(WRITE_instruction);
    SPI.transfer(addr); //Send register location
    while(len > index && page == index >> 4)
    {
      SPI.transfer(buffer[index]);
      index++;
    }

    // take the chip select high to de-select:
    digitalWrite(_cs, HIGH);
    // Hold the _cs HIGH in case we are writing to another page
    delay(5);
  }
}

/*
Microchip 25AA02E48 library

Copyright (C) 2012 Akafugu Corporation

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef MICROCHIP_25AA02E48_H
#define MICROCHIP_25AA02E48_H

#include "Arduino.h"
#include <../SPI/SPI.h>

class Microchip_25AA02E48 {
public:
	Microchip_25AA02E48(uint8_t cs);
	uint8_t readStatus();
	uint8_t readRegister(uint8_t addr);
	uint8_t readRegister(uint8_t addr, uint8_t *buffer, int len);
	void getEUI48(uint8_t *buffer);
	void getEUI64(uint8_t *buffer);
	void writeRegister(uint8_t addr, uint8_t value);
	void writeRegister(uint8_t addr, uint8_t *buffer, int len);
	
private:
	uint8_t _cs;
};

#endif // MICROCHIP_25AA02E48_H

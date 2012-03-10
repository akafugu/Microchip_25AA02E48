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

// the eeprom communicates using SPI, so include the library:
#include "SPI.h"
#include "Microchip_25AA02E48.h"

const uint8_t chipSelectPin = 6;

Microchip_25AA02E48 eeprom(chipSelectPin);

byte eui64[8];
byte eui48[6];

void setup() {
  Serial.begin(9600);

  // Make sure all other SPI devices are de-selected
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);

  // start the SPI library
  SPI.begin();
  
  eeprom.getEUI48(eui48);
  eeprom.getEUI64(eui64);
  
  Serial.print("EUI48 (hw address): ");
  if(eui48[0] < 16) Serial.print("0"); // Padding
  Serial.print(eui48[0],HEX);
  for(byte i = 1; i < 6; i++)
  {
    Serial.print("-");
    if(eui48[i] < 16) Serial.print("0"); // Padding
    Serial.print(eui48[i],HEX);
  }
  Serial.println();
  
  eeprom.getEUI64(eui64);
  
  Serial.print("EUI64: ");
  if(eui64[0] < 16) Serial.print("0"); // Padding
  Serial.print(eui64[0],HEX);
  for(byte i = 1; i < 8; i++)
  {
    Serial.print("-");
    if(eui64[i] < 16) Serial.print("0"); // Padding
    Serial.print(eui64[i],HEX);
  }
  Serial.println();
  
  // Register 0-191 is available to be written
  eeprom.writeRegister(64,0xCC);
  Serial.println("Wrote 0xCC to address 64.");
  Serial.print("Read from address 64: 0x");
  Serial.println(eeprom.readRegister(64), HEX);
}

void loop() {
}




#pragma once
/* David Johnson-Davies - www.technoblogy.com - 5th June 2022
   
   CC BY 4.0
   Licensed under a Creative Commons Attribution 4.0 International license: 
   http://creativecommons.org/licenses/by/4.0/

*/

#include <avr/io.h>
#include <stdint.h>

#if !defined(I2C_PORT) || !defined(I2C_SDA_BIT) || !defined(I2C_SCL_BIT)
  #error "Not define I2C_PORT or/and I2C_SDA/SCL";
#endif

extern void i2cInit();

extern bool i2cStart(uint8_t addressWR);

extern void i2cStop();

extern uint8_t i2cRead(bool ack);

extern bool i2cWrite(uint8_t data);

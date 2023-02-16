#pragma once

#include <stdint.h>
#include "avr-ss.h"

extern char *itoa16(int16_t value, char  *buffer);

extern u8 w1CRCBuf(void* buf, u8 len, u8 crc);

extern u8 bcd2dec(u8 bcd);
 
extern u8 dec2bcd(u8 dec);


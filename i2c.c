/* I2C synchronous master read/write using polling (no interrupts)

    flags |= fRTC_NO_ACK; // под одним флагом собираем все ошибки часов
    if(i2cStart(RTC_ADDR)){ //todo ? что именно стоит тут проверять из протокола i2c
        i2cWrite(0);
        i2cStart(RTC_ADDR + 1);
        u8 cnt = sizeof(rtc_t);
        u8* p = (u8*)&rtc;
        flags |= fRTC_NO_SET; // ломаем значение часов, поставим метку
        do{
            *(p++) = bcd2dec(i2cRead(--cnt > 0));
        } while (cnt);
        i2cStop();
        // todo # проверку значения часов придумать и добавить
        flags &= ~ (fRTC_NO_ACK | fRTC_NO_SET);  // только здесь можно очищать флаги
    }

   Натхнення i код для переробки взятi у

   David Johnson-Davies - www.technoblogy.com - 5th June 2022
   CC BY 4.0
   Licensed under a Creative Commons Attribution 4.0 International license: 
   http://creativecommons.org/licenses/by/4.0/
*/

#include "avr-ss.h"
#include "i2c.h"

#ifndef F_I2C
    #define F_I2C 400000uL
#endif   

#define TWSR_MTX_DATA_ACK   0x28
#define TWSR_MTX_ADR_ACK    0x18
#define TWSR_MRX_ADR_ACK    0x40
#define TWSR_START          0x08
#define TWSR_REP_START      0x10

#define twi_busy_wait()     loop_until_bit_is_set(TWCR, TWINT)

void i2cInit() {
    iopInputP(I2C_PORT, bv(I2C_SDA_BIT));      // Pullups on
    iopInputP(I2C_PORT, bv(I2C_SCL_BIT));
    TWSR = 0;                              // No prescaler
    TWBR = (F_CPU/F_I2C - 16)/2;        // Set bit rate factor
}

uint8_t i2cRead(bool ack) {
  TWCR = 1<<TWINT | 1<<TWEN | (ack ? (1<<TWEA) : 0);
  twi_busy_wait();
  return TWDR;
}

bool i2cWrite(uint8_t data) {
  TWDR = data;
  TWCR = 1<<TWINT | 1 << TWEN;
  twi_busy_wait();
  return (TWSR & 0xF8) == TWSR_MTX_DATA_ACK;
}

/* read: 1; write: 0 */
bool i2cStart(uint8_t addressWR) { 
    TWCR = 1<<TWINT | 1<<TWEN | 1<<TWSTA;  // Send START condition
    twi_busy_wait();
    uint8_t twsr = TWSR & 0xF8; 
    if (twsr != TWSR_START && twsr != TWSR_REP_START){
        return false;
    }
    TWDR = addressWR;   // Send device address and direction
    TWCR = 1<<TWINT | 1<<TWEN;
    twi_busy_wait();
    return (TWSR & 0xF8) == ((addressWR & 0x01) ? TWSR_MRX_ADR_ACK : TWSR_MTX_ADR_ACK);
}

void i2cStop(void) {
  TWCR = 1<<TWINT | 1<<TWEN | 1<<TWSTO;
  while (TWCR & 1<<TWSTO); // wait until stop and bus released
}

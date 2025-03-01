#include "func.h"
static int16_t pow10Table16i [] = {10000, 1000, 100, 10, 1};

char *itoa16(int16_t value, char buffer[]){
  char *ptr = buffer;
  if(value < 0){
    *ptr++ = '-';
    value = 0 - value; // abs()
  }
  if(value > 0){
    int16_t *p10 = pow10Table16i;
    while(value < *p10){ // пропускаем большие варианты вычитаемого
      p10 += 1;
    }
    while(p10 != &pow10Table16i[4]){// обработка всех вычитаемых кроме единицы
      uint8_t count = '0';
      int16_t v10 = *p10;
      *ptr = '0';
      while(value >= v10){
        count++;
        value -= v10;
      }
      *ptr++ = count ;
      p10 += 1;
    }
  }
  *ptr++ = '0' + value; // добавляем самый младший разряд
  *ptr = 0;
  return buffer;
}

u8 w1CRCBuf(void* buf, u8 len, u8 crc){
     for(u8 i = len; i > 0; i--){
         u8 b = *((u8*)buf++);
         for (uint8_t p = 8; p; p--) {
             crc = ((crc ^ b) & 1) ? (crc >> 1) ^ 0b10001100 : (crc >> 1);
             b >>= 1;
         }
     }
     return crc;
 }

u8 dec2bcd(u8 dec){
    return dec / 10 * 16 + dec % 10;
}


u8 bcd2dec(u8 bcd){
    return 10 * (bcd>>4) + (bcd & 0x0f);
}
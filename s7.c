﻿/*
–ешени¤ дл¤ работы с семисегментным индикатором

*/

#include <string.h>
#include "s7.h"

/*
  ќпределение массива знакогенератора. S7_SET можно переопределить
*/
const unsigned char  S7[] PROGMEM = {S7_SET};  // 0-9, пробел и символ P

char s7AddPoint(char* v){
  return *v |= S7_POINT;
}

void s7Str2fixPoint(char* str, char* out, uint8_t digits, uint8_t decimal){
  
  uint8_t len = strlen(str);
  
  if(len > digits + decimal){ // ошибка, данные не влаз¤т
    *out = S7_E; // подумать над выводом/сохранением ошибок...
    return;
  }

  uint8_t zero = (len > decimal)  // недостающие нули слева
      ? 0
      : decimal - len + 1;

  uint8_t remain = digits - zero; // подсчет оставшихс¤ разр¤дов (сразу отнимаем нули)

  for(int8_t i = remain - len; i > 0; i--, remain--){ // пробелы слева от числа (i может быть отрицательным)
    *out++ = S7_SPACE;
  }

  while(zero--){
    *out++ = S7_0;
  }

  char* pp = out + len - decimal; // позици¤ точки относительно начала вывода строки

  while(remain--){ // перенос данных с конвертацией
    uint8_t tmp = *str++;
//    *out++ = pgm_read_byte(&S7[*str++ - '0']);  // 922 глюк с минусом
    *out++ = ('-' == tmp) 
               ? S7_MINUS
               : pgm_read_byte(&S7[tmp - '0']); // 930
  }
  if(pp < out){ // на последнем месте точку не зажигаем
    s7AddPoint(pp - 1);
  }    
}

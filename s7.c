#include <string.h>
#include "s7.h"

/*
������� ��� ������ � �������������� �����������

*/

/*
  ����������� ������� ���������������. S7_SET ����� ��������������
*/
const unsigned char  S7[] PROGMEM = {S7_SET};  // 0-9, ������ � ������ P

void s7AddPoint(char* v){
  #ifdef S7_SEG_INVERT
    *v &= S7_POINT;
  #else
    *v |= S7_POINT;
  #endif
}

void s7Str2fixPoint(char* str, char* out, uint8_t digits, uint8_t decimal){
  
  uint8_t len = strlen(str);
  
  if(len > digits + decimal){ // ������, ������ �� ������
    *out = S7_E; // �������� ��� �������/����������� ������...
    return;
  }

  uint8_t zero = (len > decimal)  // ����������� ���� �����
      ? 0
      : decimal - len + 1;

  uint8_t remain = digits - zero; // ������� ���������� �������� (����� �������� ����)

  for(int8_t i = remain - len; i > 0; i--, remain--){ // ������� ����� �� ����� (i ����� ���� �������������)
    *out++ = S7_SPACE;
  }

  while(zero--){
    *out++ = S7_0;
  }

  char* pp = out + len - decimal; // ������� ����� ������������ ������ ������ ������

  while(remain--){ // ������� ������ � ������������
    uint8_t tmp = *str++;
//    *out++ = pgm_read_byte(&S7[*str++ - '0']);  // 922 ���� � �������
    *out++ = ('-' == tmp) 
               ? S7_MINUS
               : pgm_read_byte(&S7[tmp - '0']); // 930
  }
  if(pp < out){ // �� ��������� ����� ����� �� ��������
    s7AddPoint(pp - 1);
  }    
}

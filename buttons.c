#include "buttons.h"

static   uint8_t tbtnCurr    = 0x0; //������� ���������
static   uint8_t tbtnStable  = 0x0; //���������� ���������

#if TBTN_REPEATE_MASK > 0
uint8_t tbtnCounter = 0;    //������ ����������� //fixme ���������� ��� � �� ����� - ���������� ������ � ����� ������ ����������
#endif

#ifndef swap
  #ifdef __BUILTIN_AVR_SWAP
    #define swap(x) __builtin_avr_swap(x)
  #else  
    #define swap(A) ((A<<4)|(A>>4))
  #endif  
#endif

/* 4 ������ �� ������� ����� 0 - ������, 1 - ��������
  return ������� ���� - ���. ��������� ������ (1-������), ������� ���� - ������� ������� (1 - ���� �������) */
uint8_t tbtnProcess(uint8_t st){
  uint8_t temp;
  temp = st & 0x0f;    // 0000 pres
  tbtnStable <<= 4;    // past 0000  c������� "�������" �� ���� �����
  tbtnCurr |= temp;    // past pres  ��������� ��������� ... ������� ��� �� ����� �����
  
  // ������� �������
  temp = swap(tbtnCurr);   // pres past  "���������" �� ����� ��������
  /* ��������� ������� ������ ����� � ����� ������ 0, 
     ���� ������� � ����� �� ������, �� ������� ������ ������� */
  tbtnStable |= (tbtnCurr | (temp & 0x0f));  // past pres ��������� � stable ���� ���������� ������
  tbtnCurr = temp & 0xf0;  // pres 0000  ��������� ���������� �������
  
  //����������� ��������� ������ (����� ����. ����. � tbtnStable)
  temp = swap(tbtnStable);   // pres past  1 ��������, 0 ������
  uint8_t res = ~temp & 0xf0;// "������ ������" - ������� ����� ����������
  temp = temp ^ tbtnStable;  // past ^ pres - ������������ ���������
  temp = temp & tbtnStable;  // 7-4 ���� ������ (�������� � ���� ��������); 3-0 ���� �������� (�������� � ������ ��������)

  if (temp & 0xf0){         // ���� ���� �������
    res |= temp>>4;         // ��������� � ���������� ���� ������� ������
    #if TBTN_REPEATE_MASK > 0
    tbtnCounter = TBTN_DELAY_A;   // ��������� ������ �� ��. ��������
    #endif
  }  

  #if TBTN_REPEATE_MASK > 0
  if(tbtnCounter){ // ��� ���� �������� ������� ������ ��� ������ �������etn click
    if(0 == --tbtnCounter){     //������ �����������
      res |= ~tbtnStable & (TBTN_REPEATE_MASK); // ��������� ������� ������������ ������ � ������������
      tbtnCounter = TBTN_DELAY_B; //���������� ������� �� ���. ��������
    }
  }
  #endif
  return res;
}

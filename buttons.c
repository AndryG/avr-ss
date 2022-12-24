#include "buttons.h"

static   uint8_t tbtnCurr    = 0x0; //Текущие состояния
static   uint8_t tbtnStable  = 0x0; //Стабильные состояния

#if TBTN_REPEATE_MASK > 0
uint8_t tbtnCounter = 0;    //таймер автоповтора //fixme автоповтор тут и не нужен - переменная только в одном методе изменяется
#endif

#ifndef swap
  #ifdef __BUILTIN_AVR_SWAP
    #define swap(x) __builtin_avr_swap(x)
  #else  
    #define swap(A) ((A<<4)|(A>>4))
  #endif  
#endif

/* 4 кнопки на младших битах 0 - нажата, 1 - отпущена
  return старший нибл - тек. состояние кнопок (1-нажата), младший нибл - события нажатия (1 - было нажатие) */
uint8_t tbtnProcess(uint8_t st){
  uint8_t temp;
  temp = st & 0x0f;    // 0000 pres
  tbtnStable <<= 4;    // past 0000  cдвигаем "прошлое" на свое место
  tbtnCurr |= temp;    // past pres  добавляем настоящее ... прошлое уже на своем месте
  
  // убираем дребезг
  temp = swap(tbtnCurr);   // pres past  "настоящее" на месте прошлого
  /* стабильно нажатая кнопка имеет в обоих ниблах 0, 
     если единица в любой из частей, то считаем кнопку отжатой */
  tbtnStable |= (tbtnCurr | (temp & 0x0f));  // past pres добавляем в stable биты отпущенных кнопок
  tbtnCurr = temp & 0xf0;  // pres 0000  настоящее становится прошлым
  
  //Определение состояний кнопок (имеем стаб. сост. в tbtnStable)
  temp = swap(tbtnStable);   // pres past  1 отпущена, 0 нажата
  uint8_t res = ~temp & 0xf0;// "сейчас нажато" - верхняя часть результата
  temp = temp ^ tbtnStable;  // past ^ pres - изменившиеся состояния
  temp = temp & tbtnStable;  // 7-4 была нажата (изменена И БЫЛА отпущена); 3-0 была отпущена (изменена и ТЕПЕРЬ отпущена)

  if (temp & 0xf0){         // если было нажатие
    res |= temp>>4;         // поднимаем в результате биты нажатых кнопок
    #if TBTN_REPEATE_MASK > 0
    tbtnCounter = TBTN_DELAY_A;   // запускаем таймер на дл. задержку
    #endif
  }  

  #if TBTN_REPEATE_MASK > 0
  if(tbtnCounter){ // без этой проверки зажатая кнопка при старте генерирetn click
    if(0 == --tbtnCounter){     //таймер автоповтора
      res |= ~tbtnStable & (TBTN_REPEATE_MASK); // имитируем нажатие удерживаемых кнопок с автоповтором
      tbtnCounter = TBTN_DELAY_B; //перезапуск таймера на кор. задержку
    }
  }
  #endif
  return res;
}

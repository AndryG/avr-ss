#pragma once
#include <stdint.h>
#include <avr/builtins.h>

#define TBTN_0 0x01
#define TBTN_1 0x02
#define TBTN_2 0x04
#define TBTN_3 0x08

// #define TBTN_REPEATE_MASK BTN_0 | BTN_1; Кнопки для автоповтора

// Задержки автоповтора по умолчанию для опроса кнопок 50мс
#ifndef TBTN_DELAY_A
  #define TBTN_DELAY_A      10
#endif

#ifndef TBTN_DELAY_B
  #define TBTN_DELAY_B      2
#endif

extern uint8_t tbtnProcess(uint8_t);
  


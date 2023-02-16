#ifndef S7_include
#define S7_include
/*
  Настраиваемый знакогенератор для семисегментного индикатора
  a.hordieiev@ukr.net 2009-2021
--------------------------------------------------------------------------------
  До вставки этого файла необходимо определить:

   1. Привязка "бит-сегмент" (по умолчанию A-0,B-1..P-7)
       #define S7_SEG_A 0  (Сегмент А -- висит на бите 0)
       .. B C D E F G
       #define S7_SEG_P 7  (Сегмент P -- висит на бите 7) -- это точка
       Расположение сегментов см. ниже

   2. Z7_SET можно сформировать массив знакогенератора. По умолчанию в нем только цифры
        Например: S7_NUMS, S7_SPACE, S7_CHAR(1,1,0,0,1,1,1,0)

--------------------------------------------------------------------------------
  ПОСЛЕ #include ZG7.h мы получим в использование определения символов S7_*
     Из них нужно сформировать и объявить массив знакогненератора S7, который в этом файле оишь объявлен.
  Например (main.c avr-gcc):
    const unsigned char PROGMEM S7[] = {S7_SET, S7_MINUS}; // 0-9 и минус

--------------------------------------------------------------------------------
  Расположение сегментов в индикаторе

  ??A??
  F   B
  ??G??
  E   C
  ??D??P

*/

#include <avr/pgmspace.h>

//Значеие по умолчанию для связки бит-сегмент
#ifndef S7_SEG_A
  #define S7_SEG_A 0
#endif
#ifndef S7_SEG_B
  #define S7_SEG_B 1
#endif
#ifndef S7_SEG_C
  #define S7_SEG_C 2
#endif
#ifndef S7_SEG_D
  #define S7_SEG_D 3
#endif
#ifndef S7_SEG_E
  #define S7_SEG_E 4
#endif
#ifndef S7_SEG_F
  #define S7_SEG_F 5
#endif
#ifndef S7_SEG_G
  #define S7_SEG_G 6
#endif
#ifndef S7_SEG_P
  #define S7_SEG_P 7
#endif

//Макрос "сборки" байта знакогенератора из определений "бит-сегмент" и "полярность поджига" (1/0-зажечь/потушить).
  #define S7_CHAR(xA,xB,xC,xD,xE,xF,xG,xP) ((unsigned char)((xA<<S7_SEG_A)|(xB<<S7_SEG_B)|(xC<<S7_SEG_C)|(xD<<S7_SEG_D)|(xE<<S7_SEG_E)|(xF<<S7_SEG_F)|(xG<<S7_SEG_G)|(xP<<S7_SEG_P)))
  #define S7_ADD_POINT(buf) ((buf) |= S7_POINT)

//Небольшие макросы для пробела/забоя/точки/цифр
#define S7_SPACE    S7_CHAR(0,0,0,0,0,0,0,0)
#define S7_ALL      S7_CHAR(1,1,1,1,1,1,1,0)
#define S7_POINT    S7_CHAR(0,0,0,0,0,0,0,1)
#define S7_MINUS    S7_CHAR(0,0,0,0,0,0,1,0)
#define S7_0        S7_CHAR(1,1,1,1,1,1,0,0)
#define S7_1        S7_CHAR(0,1,1,0,0,0,0,0)
#define S7_2        S7_CHAR(1,1,0,1,1,0,1,0)
#define S7_3        S7_CHAR(1,1,1,1,0,0,1,0)
#define S7_4        S7_CHAR(0,1,1,0,0,1,1,0)
#define S7_5        S7_CHAR(1,0,1,1,0,1,1,0)
#define S7_6        S7_CHAR(1,0,1,1,1,1,1,0)
#define S7_7        S7_CHAR(1,1,1,0,0,0,0,0)
#define S7_8        S7_CHAR(1,1,1,1,1,1,1,0)
#define S7_9        S7_CHAR(1,1,1,1,0,1,1,0)
#define S7_A        S7_CHAR(1,1,1,0,1,1,1,0)
#define S7_b        S7_CHAR(0,0,1,1,1,1,1,0)
#define S7_c        S7_CHAR(0,0,0,1,1,0,1,0)
#define S7_C        S7_CHAR(1,0,0,1,1,1,0,0)
#define S7_d        S7_CHAR(0,1,1,1,1,0,1,0)
#define S7_E        S7_CHAR(1,0,0,1,1,1,1,0)
#define S7_F        S7_CHAR(1,0,0,0,1,1,1,0)
#define S7_G        S7_CHAR(1,0,1,1,1,1,0,0)
#define S7_h        S7_CHAR(0,0,1,0,1,1,1,0)
#define S7_j        S7_CHAR(0,1,1,1,0,0,0,0)
#define S7_L        S7_CHAR(0,0,0,1,1,1,0,0)
#define S7_n        S7_CHAR(0,0,1,0,1,0,1,0)
#define S7_o        S7_CHAR(0,0,1,1,1,0,1,0)
#define S7_P        S7_CHAR(1,1,0,0,1,1,1,0)
#define S7_r        S7_CHAR(0,0,0,0,1,0,1,0)
#define S7_S        S7_CHAR(1,0,1,1,0,1,1,0)
#define S7_t        S7_CHAR(0,0,0,1,1,1,1,0)
#define S7_u        S7_CHAR(0,0,1,1,1,0,0,0)
//#define S7_      S7_CHAR(0,0,0,0,0,0,0,0)

/*
  S7_SET макрос с содержимым масива знакогенератора.
  По умолчанию в него вставляется лишь набор чисел.
  Можно переопределеить S7_SET, сформировав нужный набор кодов. Учти, что цифры в начале массива нужны для функций форматирования.
*/
#ifndef S7_SET
  #define S7_SET S7_0, S7_1, S7_2, S7_3, S7_4, S7_5, S7_6, S7_7, S7_8, S7_9
#endif

// Объявление массива знакогенератора
#ifdef __GNUC__                     // GNU Compiler
  extern const unsigned char PROGMEM S7[];
#elif defined(__CODEVISIONAVR__)    // CodeVision
  extern flash unsigned char S7[];
#elif defined(__ICCAVR__)           // IAR C Compiler
  extern __flash unsigned char S7[];
#else
  #error Unknown compiler
#endif

/*
  Принимает строку, заполняет видеопамять якобы в буфере число с расчетом dig знаков в индикаторе, dec знаков после запятой
  Пустое место забивается  S7_SPACE, проставляются недостающие нули S7_0 и ставится точка.
    ?? Добавляет второй цикл, но зато Буфер должен содержать уже коды для видеопамяти, а не число
  Если число слишком большое, то выводится "00".
  @todo по хорошему тут бы выпасть в большую ошибку и сохранить её код.
*/
extern void s7Str2fixPoint(char* buf, char* v, uint8_t digits, uint8_t decimal);

extern char s7AddPoint(char* v);

#endif

/*  i8 n = dec + 1 - len;        // 1180
  if(n < 0){
    n = 0;
  }
  i8 s = dig - n - len;
  if(s < 0){
    s = 0;
  }
  char* v = video;
  char* b = buf;
  for(i8 i = 0 - s - n; i < dig - s - n; i++){
    if(i < 0 - n){
      *v++ = S7_space;
    }else if(i < 0){
      *v++ = ZG7[0];
    }else{
      *v++ = pgm_read_byte(&ZG7[*b++ - '0']);
    }
  }


*/
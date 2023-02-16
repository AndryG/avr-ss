#ifndef S7_include
#define S7_include
/*
  ������������� �������������� ��� ��������������� ����������
  a.hordieiev@ukr.net 2009-2021
--------------------------------------------------------------------------------
  �� ������� ����� ����� ���������� ����������:

   1. �������� "���-�������" (�� ��������� A-0,B-1..P-7)
       #define S7_SEG_A 0  (������� � -- ����� �� ���� 0)
       .. B C D E F G
       #define S7_SEG_P 7  (������� P -- ����� �� ���� 7) -- ��� �����
       ������������ ��������� ��. ����

   2. Z7_SET ����� ������������ ������ ���������������. �� ��������� � ��� ������ �����
        ��������: S7_NUMS, S7_SPACE, S7_CHAR(1,1,0,0,1,1,1,0)

--------------------------------------------------------------------------------
  ����� #include ZG7.h �� ������� � ������������� ����������� �������� S7_*
     �� ��� ����� ������������ � �������� ������ ���������������� S7, ������� � ���� ����� ���� ��������.
  �������� (main.c avr-gcc):
    const unsigned char PROGMEM S7[] = {S7_SET, S7_MINUS}; // 0-9 � �����

--------------------------------------------------------------------------------
  ������������ ��������� � ����������

  ??A??
  F   B
  ??G??
  E   C
  ??D??P

*/

#include <avr/pgmspace.h>

//������� �� ��������� ��� ������ ���-�������
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

//������ "������" ����� ��������������� �� ����������� "���-�������" � "���������� �������" (1/0-������/��������).
  #define S7_CHAR(xA,xB,xC,xD,xE,xF,xG,xP) ((unsigned char)((xA<<S7_SEG_A)|(xB<<S7_SEG_B)|(xC<<S7_SEG_C)|(xD<<S7_SEG_D)|(xE<<S7_SEG_E)|(xF<<S7_SEG_F)|(xG<<S7_SEG_G)|(xP<<S7_SEG_P)))
  #define S7_ADD_POINT(buf) ((buf) |= S7_POINT)

//��������� ������� ��� �������/�����/�����/����
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
  S7_SET ������ � ���������� ������ ���������������.
  �� ��������� � ���� ����������� ���� ����� �����.
  ����� ��������������� S7_SET, ����������� ������ ����� �����. ����, ��� ����� � ������ ������� ����� ��� ������� ��������������.
*/
#ifndef S7_SET
  #define S7_SET S7_0, S7_1, S7_2, S7_3, S7_4, S7_5, S7_6, S7_7, S7_8, S7_9
#endif

// ���������� ������� ���������������
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
  ��������� ������, ��������� ����������� ����� � ������ ����� � �������� dig ������ � ����������, dec ������ ����� �������
  ������ ����� ����������  S7_SPACE, ������������� ����������� ���� S7_0 � �������� �����.
    ?? ��������� ������ ����, �� ���� ����� ������ ��������� ��� ���� ��� �����������, � �� �����
  ���� ����� ������� �������, �� ��������� "00".
  @todo �� �������� ��� �� ������� � ������� ������ � ��������� � ���.
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
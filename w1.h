/*
 * Created: 09.01.2022 15:43:48
 *  a.hordieiev@ukr.net
 */
/* https://aterlux.ru/article/1wire */

#include <avr/io.h>
#include <util/atomic.h>
#include <util/delay.h>


#define W1_PORT PORTD

#define W1_BIT  PD3

uint8_t w1Reset(void);

uint8_t w1rw( uint8_t data );

uint8_t w1CRCUpdate(uint8_t crc, uint8_t b);

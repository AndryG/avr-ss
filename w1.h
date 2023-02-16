/*
 * Created: 09.01.2022 15:43:48
 *  a.hordieiev@ukr.net
 * https://aterlux.ru/article/1wire
 * https://avr.ru/beginer/understand/1wire
 */

#include <avr/io.h>
#include <util/atomic.h>
#include <util/delay.h>

#ifndef W1_PORT
    #error "W1_PORT not defined. Set port for one-wire"
#endif
#ifndef W1_BIT
    #error "W1_BIT not defined. Set bit for one-wire"
#endif

uint8_t w1Reset(void);

uint8_t w1rw( uint8_t data );

uint8_t w1CRCUpdate(uint8_t crc, uint8_t b);

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <util/atomic.h>

typedef uint8_t   u8;
typedef int8_t    i8;
typedef uint16_t  u16;
typedef int16_t   i16;
typedef uint32_t  u32;
typedef int32_t   i32;

typedef volatile uint8_t port_t;

//#define delay_us(us)     __delay_cycles((F_CPU / 1000000) * (us));
//#define delay_ms(ms)     __delay_cycles((F_CPU / 1000) * (ms));

#define bv(x)   _BV(x)

#define IOP_DDR(port)   (*(port_t*)(&(port) - 1))

#define IOP_PIN(port)   (*(port_t*)(&(port) - 2))

#define iopDirSet(port, data) IOP_DDR(port) = (data)

#define iopOutputHigh(port, mask) port |= (mask); IOP_DDR(port) |= (mask)

#define iopOutputLow(port, mask) port &= ~(mask); IOP_DDR(port) |= (mask)

#define iopOutputSet(port, data) port = (data); IOP_DDR(port) = (data)

#define iopOutput(port, mask) IOP_DDR(port) |= (mask)

#define iopInput(port, mask)  IOP_DDR(port) &= ~(mask)

#define iopInputP(port, mask)  IOP_DDR(port) &= ~(mask); port |= (mask)

#define iopInputZ(port, mask)  IOP_DDR(port) &= ~(mask); port &= ~(mask)

#define iopSet(port, data)  port = (data)

#define iopLow(port, mask)  port &= ~(mask)

#define iopHigh(port, mask)  port |= (mask)

#define iopPin(port) IOP_PIN(port)

#define iopBit(port, bit) (IOP_PIN(port) & (1 << bit))

//#define swap(x) __asm__ __volatile__ ("swap %0" : "=r" (x) : "0" (x))
//#define swap(a) ((a<<4) | (a>>4))

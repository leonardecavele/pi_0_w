#ifndef UART_H
#define UART_H

#include "standard.h"
#include "address.h"
#include "bcm2835.h"

#define BASE10 "0123456789"
#define BASE16 "0123456789abcdef"

#define UART_CLK 3000000u
#define UART_BAUD 115200u

/* get bit 'c' from uart register 'a' + offset 'b' */
#define UART_GET_BIT(a, b, c) \
	((REG4B((a) + (b)) >> (uint32_t)(c)) & 1u)

typedef enum e_uart_offset {
	DR_OFFSET = 0x00u,
	RSRECR_OFFSET = 0x04u,
	FR_OFFSET = 0x18u,
	IBRD_OFFSET = 0x24u,
	FBRD_OFFSET = 0x28u,
	LCRH_OFFSET = 0x2cu,
	CR_OFFSET = 0x30u,
	IFLS_OFFSET = 0x34u,
	IMSC_OFFSET = 0x38u,
	RIS_OFFSET = 0x3cu,
	MIS_OFFSET = 0x40u,
	ICR_OFFSET = 0x44u
} t_uart_offset;

typedef enum e_uart_fr_bit {
	FR_CTS = 0,
	FR_BUSY = 3,
	FR_RXFE = 4,
	FR_TXFF = 5,
	FR_RXFF = 6,
	FR_TXFE = 7
} t_uart_fr_bit;

typedef enum e_uart_lcrh_bit {
	LCRH_BRK = 0,
	LCRH_PEN = 1,
	LCRH_EPS = 2,
	LCRH_STP2 = 3,
	LCRH_FEN = 4,
	LCRH_WLEN_SHIFT = 5,
	LCRH_SPS = 7
} t_uart_lcrh_bit;

typedef enum e_uart_cr_bit {
	CR_UARTEN = 0,
	CR_TXE = 8,
	CR_RXE = 9,
	CR_RTS = 11,
	CR_RTSEN = 14,
	CR_CTSEN = 15
} t_uart_cr_bit;

typedef enum e_uart_mask {
	LCRH_WLEN_MASK = 0x3u,
	LCRH_WLEN_8BIT = 0x3u,
	UART_ICR_ALL = 0x07ffu
} t_uart_mask;

void uart_init(uintptr_t t, uint32_t clk, uint32_t baud);
void uart_putc(uintptr_t t, char c);
void uart_putstr(uintptr_t t, const char *s);
void uart_putnbr(uintptr_t t, int32_t n, const char *base, uint32_t len);
void uart_putunbr(uintptr_t t, uint32_t n, const char *base, uint32_t len);
void uart_printf(uintptr_t t, const char *s, ...);
char uart_getc(uintptr_t t);

#endif

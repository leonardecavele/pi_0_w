#include "standard.h"
#include "address.h"
#include "gpio.h"
#include "uart.h"

static uint32_t uart_get_ibrd(uint32_t clk, uint32_t baud)
{
	uint32_t	div;

	if (baud == 0u)
		return (0u);
	div = ((clk * 4u) + (baud / 2u)) / baud;
	return (div / 64u);
}

static uint32_t uart_get_fbrd(uint32_t clk, uint32_t baud)
{
	uint32_t	div;

	if (baud == 0u)
		return (0u);
	div = ((clk * 4u) + (baud / 2u)) / baud;
	return (div % 64u);
}

extern void uart_init(uintptr_t t, uint32_t clk, uint32_t baud)
{
	uint32_t	lcrh;

	REG4B(t + CR_OFFSET) = 0u;
	REG4B(t + ICR_OFFSET) = UART_ICR_ALL;
	REG4B(t + IBRD_OFFSET) = uart_get_ibrd(clk, baud);
	REG4B(t + FBRD_OFFSET) = uart_get_fbrd(clk, baud);
	lcrh = 0u;
	lcrh |= (LCRH_WLEN_8BIT << LCRH_WLEN_SHIFT);
	lcrh |= (1u << LCRH_FEN);
	REG4B(t + LCRH_OFFSET) = lcrh;
	REG4B(t + IMSC_OFFSET) = 0u;
	REG4B(t + CR_OFFSET) = (1u << CR_UARTEN) | (1u << CR_TXE) | (1u << CR_RXE);
}

extern void uart_putc(uintptr_t t, char c)
{
	while (UART_GET_BIT(t, FR_OFFSET, FR_TXFF)) { }
	REG4B(t + DR_OFFSET) = (uint32_t)(unsigned char)c;
}

extern void uart_putstr(uintptr_t t, const char *s)
{
	char	c;

	while ((c = *s++))
		uart_putc(t, c);
}

extern void uart_putnbr(uintptr_t t, int32_t n, const char *b, uint32_t l)
{
	if (n < 0) { uart_putc(t, '-'); n = -n; }
	if (n >= (int32_t)l) { uart_putnbr(t, n / (int32_t)l, b, l); }
	uart_putc(t, (b[n % (int32_t)l]));
}

extern void uart_putunbr(uintptr_t t, uint32_t n, const char *b, uint32_t l)
{
	if (n >= l) { uart_putunbr(t, n / l, b, l); }
	uart_putc(t, (b[n % l]));
}

static void uart_putpm(uintptr_t t, va_list *pm, char c)
{
	switch (c) {
		case 'p':
			uart_putstr(t, "0x");
			uart_putunbr(t, (uintptr_t)va_arg(*pm, void *), BASE16, 16u);
			break;
		case 'c':
			uart_putc(t, va_arg(*pm, int)); break;
		case 's':
			uart_putstr(t, va_arg(*pm, const char *)); break;
		case 'd':
			uart_putnbr(t, va_arg(*pm, int), BASE10, 10u); break;
		case 'u':
			uart_putunbr(t, va_arg(*pm, uint_t), BASE10, 10u); break;
		case 'x':
			uart_putunbr(t, va_arg(*pm, uint_t), BASE16, 16u); break;
		case '%':
			uart_putc(t, '%'); break;
		default:
			uart_putstr(t, "{unknown type}"); break;
	}
}

extern void uart_printf(uintptr_t t, const char *s, ...)
{
	va_list	pm;

	va_start(pm, s);
	do {
		if (*s == '%') { uart_putpm(t, &pm, *++s); }
		else { uart_putc(t, *s); }
	} while (*s++);
	va_end(pm);
}

extern char uart_getc(uintptr_t t)
{
	while (UART_GET_BIT(t, FR_OFFSET, FR_RXFE)) { }
	return ((char)(REG4B(t + DR_OFFSET) & 0xffu));
}

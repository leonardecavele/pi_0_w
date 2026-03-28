#include "gpio.h"
#include "uart.h"

int kmain(uintptr_t dtb)
{
	/* todo
	   uart
	   sleep
	   gpio (led, button (signals))
	   screen
	*/

	gpio_set_func(14u, GPIO_ALT0);
	gpio_set_pull(14u, GPIO_PULL_DOWN);
	gpio_set_func(15u, GPIO_ALT0);
	gpio_set_pull(15u, GPIO_PULL_DOWN);
	uart_init(BCM2835_UART0, UART_CLK, UART_BAUD);

	uart_printf(BCM2835_UART0, "hello world\r\n");

	/* cpu hang */
	while (1) {}
}

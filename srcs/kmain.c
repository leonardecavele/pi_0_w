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

	gpio_set_func(17u, GPIO_OUTPUT);
	gpio_write(17u, 1);
	gpio_set_func(27u, GPIO_OUTPUT);
	gpio_write(27u, 1);
	gpio_set_func(22u, GPIO_OUTPUT);
	gpio_write(27u, 1);

	gpio_set_func(14u, GPIO_ALT0);
	gpio_set_pull(14u, GPIO_PULL_OFF);
	gpio_set_func(15u, GPIO_ALT0);
	gpio_set_pull(15u, GPIO_PULL_OFF);
	uart_init(BCM2835_UART0, UART_CLK, UART_BAUD);

	uart_printf(BCM2835_UART0, "hello world\r\n");

	/* cpu hang */
	while (1) {}
}

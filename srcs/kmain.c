#include "gpio.h"
#include "uart.h"
#include "command.h"

int kmain(uintptr_t dtb)
{
	/* todo
	   uart
	   sleep
	   gpio (led, button (signals))
	   screen
	*/

	/* set-up leds GPIO */
	gpio_set_func(17u, GPIO_OUTPUT);
	gpio_set_func(27u, GPIO_OUTPUT);
	gpio_set_func(22u, GPIO_OUTPUT);

	/* set-up UART0 GPIO */
	gpio_set_func(14u, GPIO_ALT0);
	gpio_set_pull(14u, GPIO_PULL_OFF);
	gpio_set_func(15u, GPIO_ALT0);
	gpio_set_pull(15u, GPIO_PULL_OFF);
	/* INIT UART0 */
	uart_init(BCM2835_UART0, UART_CLK, UART_BAUD);

	/* UART test */
	uart_printf(BCM2835_UART0, "hello world\r\n");

	/* cpu hang */
	while (1) {
		wait_cmd(BCM2835_UART0);
	}
}

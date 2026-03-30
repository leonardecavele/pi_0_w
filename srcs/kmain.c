#include "gpio.h"
#include "uart.h"
#include "command.h"

static bool g_led_state = false;

void handle_irq(void)
{
	if (gpio_event_pending(23u))
	{
		gpio_event_clear(23u);
		g_led_state = !g_led_state;
		gpio_write(17u, g_led_state);
	}
}

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

	/* set-up button GPIO */
	gpio_set_func(23u, GPIO_INPUT);
	gpio_set_pull(23u, GPIO_PULL_UP);
	gpio_event_clear(23u);
	gpio_enable_falling(23u);

	/* set-up UART0 GPIO */
	gpio_set_func(14u, GPIO_ALT0);
	gpio_set_pull(14u, GPIO_PULL_OFF);
	gpio_set_func(15u, GPIO_ALT0);
	gpio_set_pull(15u, GPIO_PULL_OFF);
	/* init UART0 */
	uart_init(BCM2835_UART0, UART_CLK, UART_BAUD);

	/* UART test */
	uart_printf(BCM2835_UART0, "hello world\r\n");
	//wait_cmd(BCM2835_UART0);

	/* cpu hang */
	while (1) {
		sleep();
	}
}

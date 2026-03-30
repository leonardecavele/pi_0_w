#include "gpio.h"
#include "uart.h"
#include "command.h"
#include "irq.h"

static volatile bool g_int23_button = false;

void handle_irq(void)
{
	if (gpio_event_pending(23u))
	{
		gpio_event_clear(23u);
		g_int23_button = true;
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

	/* enable bcm2835 IRQ */
	REG4B(BCM2835_IRQ + IRQ_ENABLE_2) = IRQ_GPIO_BANK0_BIT;

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

	bool led_state = false;
	/* cpu hang */
	while (1) {
		if (g_int23_button)
		{
			g_int23_button = false;
			led_state = !led_state;
			gpio_write(17u, led_state);
			gpio_write(27u, led_state);
			gpio_write(22u, led_state);
			uart_printf(BCM2835_UART0, "interrupt 23\r\n");
		}
		sleep();
	}
}

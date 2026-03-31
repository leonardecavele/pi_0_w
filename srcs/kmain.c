#include "gpio.h"
#include "uart.h"
#include "command.h"
#include "irq.h"
#include "time.h"

#define TARGET_FPS 1u
#define FRAME_US (1000000u / TARGET_FPS)

static volatile bool g_int23_button = false;
static volatile bool g_int24_button = false;
static volatile bool g_int25_button = false;
static volatile bool g_int26_button = false;

void handle_irq(void)
{
	if (gpio_event_pending(23u)) {
		gpio_event_clear(23u);
		g_int23_button = true;
	}
	if (gpio_event_pending(24u)) {
		gpio_event_clear(24u);
		g_int24_button = true;
	}
	if (gpio_event_pending(25u)) {
		gpio_event_clear(25u);
		g_int25_button = true;
	}
	if (gpio_event_pending(26u)) {
		gpio_event_clear(26u);
		g_int26_button = true;
	}
}

int kmain(uintptr_t dtb)
{
	(void)dtb;

	/* set-up UART0 GPIO */
	gpio_set_func(14u, GPIO_ALT0);
	gpio_set_pull(14u, GPIO_PULL_OFF);
	gpio_set_func(15u, GPIO_ALT0);
	gpio_set_pull(15u, GPIO_PULL_OFF);
	/* init UART0 */
	uart_init(BCM2835_UART0, UART_CLK, UART_BAUD);
	/* UART test */
	uart_printf(BCM2835_UART0, "hello world\r\n");
	wait_cmd(BCM2835_UART0);

	/* set-up button GPIO 23 */
	gpio_set_func(23u, GPIO_INPUT);
	gpio_set_pull(23u, GPIO_PULL_UP);
	gpio_event_clear(23u);
	gpio_enable_falling(23u);
	gpio_event_clear(23u);

	/* set-up button GPIO 24 */
	gpio_set_func(24u, GPIO_INPUT);
	gpio_set_pull(24u, GPIO_PULL_UP);
	gpio_event_clear(24u);
	gpio_enable_falling(24u);
	gpio_event_clear(24u);

	/* set-up button GPIO 25 */
	gpio_set_func(25u, GPIO_INPUT);
	gpio_set_pull(25u, GPIO_PULL_UP);
	gpio_event_clear(25u);
	gpio_enable_falling(25u);
	gpio_event_clear(25u);

	/* set-up button GPIO 26 */
	gpio_set_func(26u, GPIO_INPUT);
	gpio_set_pull(26u, GPIO_PULL_UP);
	gpio_event_clear(26u);
	gpio_enable_falling(26u);
	gpio_event_clear(26u);

	irq_controller_reset();
	irq_controller_enable(IRQ_GPIO_BANK0);
	irq_enable();

	/* main loop */
	uint32_t excess = 0u;
	while (1) {
		uint32_t start_us = get_time_us();

		if (g_int23_button) {
			g_int23_button = false;
		}
		if (g_int24_button) {
			g_int24_button = false;
		}
		if (g_int25_button) {
			g_int25_button = false;
		}
		if (g_int26_button) {
			g_int26_button = false;
		}

		uint32_t elapsed_us = (get_time_us() - start_us) + excess;


		uart_printf(
			BCM2835_UART0,
			"now=%u us | frame=%u us | excess=%u\r\n",
			get_time_us(), elapsed_us, excess
		);

		if (elapsed_us < FRAME_US) {
			usleep(FRAME_US - elapsed_us);
			excess = 0u;
		}
		else
			excess = elapsed_us - FRAME_US;
	}
}

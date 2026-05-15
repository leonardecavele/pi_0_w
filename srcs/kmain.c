#include "drivers/uart.h"
#include "drivers/irq.h"
#include "drivers/spi.h"
#include "drivers/st7735.h"
#include "helpers/time.h"
#include "system/mapping.h"
#include "system/buttons.h"
#include "app/app.h"
#include "app/snake/snake.h"

int	kmain(void)
{
	static uint16_t	fb[160u * 128u];
	t_st7735		st7735;
	t_display		display;
	t_core			core;
	uint32_t		last_frame_us;
	uint32_t		current_frame_us;
	uint32_t		frame_time;

	mapping_uart();
	mapping_spi();
	mapping_display();
	mapping_buttons();
	uart_init(BCM2835_UART0, UART_CLK, UART_BAUD);
	uart_printf(BCM2835_UART0, "UART OK\r\n");
	uart_printf(BCM2835_UART0, "setting up IRQ\r\n");
	init_irq();
	register_irq(IRQ_GPIO_BANK0, buttons_irq_handler, 0);
	enable_line_irq(IRQ_GPIO_BANK0);
	enable_irq();
	uart_printf(BCM2835_UART0, "IRQ set up\r\n");
	uart_printf(BCM2835_UART0, "setting up DISPLAY\r\n");
	st7735 = (t_st7735){
		.pins = {
			.dc_gpio = DISPLAY_DC_GPIO,
			.rst_gpio = DISPLAY_RST_GPIO
		},
		.clk_div = 64u,
		.spi_mode = SPI_MODE0,
		.madctl = ST7735_MADCTL_MV | ST7735_MADCTL_MX,
		.colmod = ST7735_COLMOD_16BIT
	};
	display = (t_display){
		.width = 160u,
		.height = 128u,
		.driver = &st7735,
		.fn = &st7735_fn,
		.fb = fb
	};
	display_init(&display);
	uart_printf(BCM2835_UART0, "DISPLAY set up\r\n");
	core = (t_core){
		.display = &display
	};
	snake_init(&core);
	uart_printf(BCM2835_UART0, "starting CORE\r\n");
	last_frame_us = get_time_us();
	while (1)
	{
		current_frame_us = get_time_us();
		core.dt = current_frame_us - last_frame_us;
		last_frame_us = current_frame_us;
		if (core.current_view != 0)
		{
			core.current_view->update(core.current_view->app_data);
			core.current_view->draw(core.current_view->app_data);
		}
		frame_time = get_time_us() - current_frame_us;
		if (frame_time < FRAME_US)
			usleep(FRAME_US - frame_time);
	}
	return (0);
}

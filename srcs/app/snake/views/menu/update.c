#include "drivers/uart.h"
#include "app/snake/snake.h"
#include "system/buttons.h"
#include "helpers/standard.h"

static bool update_buttons(t_snake_menu_state *menu_state)
{
	if (button_left() || button_up() || button_right() || button_down()) {
		uart_printf(BCM2835_UART0, "snake: button pressed\r\n");
		return true;
	}
	return false;
}

extern void snake_menu_update(void *app_data)
{
	t_snake_app *snake_app = app_data;

	if update_buttons(&snake_app->menu_state);
}

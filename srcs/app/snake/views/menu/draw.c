#include "app/snake/snake.h"
#include "display/draw.h"

static void draw_menu_background(
	t_display *display, t_snake_draw *snake_draw
)
{
	draw_fill_rectangle(
		display,
		snake_draw->offset_x,
		snake_draw->offset_y,
		GRID_WIDTH * snake_draw->cell_size,
		GRID_HEIGHT * snake_draw->cell_size,
		SNAKE_MENU_BACKGROUND
	);
}
extern void snake_menu_draw(void *app_data)
{
	t_snake_app *snake_app = app_data;
	t_display *display = snake_app->core->display;
	t_snake_draw *snake_draw = &snake_app->draw;
	t_snake_menu_state menu_state = snake_app->menu_state;

	draw_clear(display, SNAKE_BACKGROUND);
	draw_menu_background(display, snake_draw);
	display_flush_fb(display);
}

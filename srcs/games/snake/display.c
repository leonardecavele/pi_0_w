#include "display/display.h"
#include "display/draw.h"
#include "app/snake/logic.h"
#include "app/snake/display.h"

static void draw_cell(
	t_display *display, t_snake_display *snake_display,
	uint16_t grid_x, uint16_t grid_y, uint16_t color
)
{
	if (grid_x >= GRID_WIDTH || grid_y >= GRID_HEIGHT)
		return ;

	draw_fill_rectangle(
		display,
		snake_display->offset_x + (grid_x * snake_display->cell_size),
		snake_display->offset_y + (grid_y * snake_display->cell_size),
		snake_display->cell_size,
		snake_display->cell_size,
		color
	);
}

static void draw_game_background(
	t_display *display, t_snake_display *snake_display
)
{
	draw_fill_rectangle(
		display,
		snake_display->offset_x,
		snake_display->offset_y,
		GRID_WIDTH * snake_display->cell_size,
		GRID_HEIGHT * snake_display->cell_size,
		SNAKE_GAME_BACKGROUND
	);
}

static void	draw_fruit(
	t_display *display, t_snake_display *snake_display, t_snake_state state
)
{
	if (state.fruit.active)
		draw_cell(
			display,
			snake_display,
			state.fruit.pos.v1,
			state.fruit.pos.v2,
			(uint16_t)SNAKE_FRUIT_COLOR
		);
}

static void draw_snake_body(
	t_display *display, t_snake_display *snake_display, t_snake_state state
)
{
	for (uint16_t i = 0; i < state.length; i++) {
		draw_cell(
			display,
			snake_display,
			state.body[(state.head - i + SNAKE_MAX_LEN) % SNAKE_MAX_LEN].v1,
			state.body[(state.head - i + SNAKE_MAX_LEN) % SNAKE_MAX_LEN].v2,
			(uint16_t)SNAKE_BODY_COLOR
		);
	}
}

/* ADD VIEWS ! */

/* every frame */
extern void draw_snake(
	t_display *display, t_snake_display *snake_display, t_snake_state state
)
{
	draw_clear(display, SNAKE_BACKGROUND);
	draw_game_background(display, snake_display);
	draw_snake_body(display, snake_display, state);
	draw_fruit(display, snake_display, state);
	display_flush_fb(display);
}

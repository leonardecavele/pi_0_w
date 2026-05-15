#include "app/snake/snake.h"
#include "app/snake/views/game.h"
#include "display/draw.h"

static void draw_cell(
	t_display *display, t_snake_draw *snake_draw,
	uint16_t grid_x, uint16_t grid_y, uint16_t color
)
{
	if (grid_x >= GRID_WIDTH || grid_y >= GRID_HEIGHT)
		return ;
	draw_fill_rectangle(
		display,
		snake_draw->offset_x + (grid_x * snake_draw->cell_size),
		snake_draw->offset_y + (grid_y * snake_draw->cell_size),
		snake_draw->cell_size,
		snake_draw->cell_size,
		color
	);
}

static void draw_game_background(
	t_display *display, t_snake_draw *snake_draw
)
{
	draw_fill_rectangle(
		display,
		snake_draw->offset_x,
		snake_draw->offset_y,
		GRID_WIDTH * snake_draw->cell_size,
		GRID_HEIGHT * snake_draw->cell_size,
		SNAKE_GAME_BACKGROUND
	);
}

static void draw_fruit(
	t_display *display, t_snake_draw *snake_draw, t_snake_state state
)
{
	if (state.fruit.active)
		draw_cell(
			display,
			snake_draw,
			state.fruit.pos.v1,
			state.fruit.pos.v2,
			(uint16_t)SNAKE_FRUIT_COLOR
		);
}

static void draw_snake_body(
	t_display *display, t_snake_draw *snake_draw, t_snake_state state
)
{
	for (uint16_t i = 0; i < state.length; i++)
	{
		draw_cell(
			display,
			snake_draw,
			state.body[(state.head - i + SNAKE_MAX_LEN) % SNAKE_MAX_LEN].v1,
			state.body[(state.head - i + SNAKE_MAX_LEN) % SNAKE_MAX_LEN].v2,
			(uint16_t)SNAKE_BODY_COLOR
		);
	}
}

extern void snake_game_draw(void *app_data)
{
	t_snake_app *snake_app = app_data;
	t_display *display = snake_app->core->display;
	t_snake_draw *snake_draw = &snake_app->draw;
	t_snake_state state = snake_app->state;

	draw_clear(display, SNAKE_BACKGROUND);
	draw_game_background(display, snake_draw);
	draw_snake_body(display, snake_draw, state);
	draw_fruit(display, snake_draw, state);
	display_flush_fb(display);
}

#include "helpers/math.h"
#include "app/snake/snake.h"
#include "app/snake/update.h"

static void	snake_update(void *app_data)
{
	snake_step(app_data);
}

static void	snake_draw(void *app_data)
{
	t_snake_app	*snake_app;

	snake_app = app_data;
	draw_snake(
		snake_app->core->display,
		&snake_app->display,
		snake_app->state
	);
}

extern void	snake_init(t_core *core)
{
	static t_snake_app	snake_app;
	t_display			*display;
	uint16_t			cell_size;

	display = core->display;
	cell_size = min(
		display->width / GRID_WIDTH, display->height / GRID_HEIGHT
	);
	snake_app.core = core;
	snake_app.display = (t_snake_display){
		.cell_size = cell_size,
		.offset_x = (display->width - (GRID_WIDTH * cell_size)) / 2u,
		.offset_y = (display->height - (GRID_HEIGHT * cell_size)) / 2u,
		.game_width = GRID_WIDTH * cell_size,
		.game_height = GRID_HEIGHT * cell_size
	};
	snake_app.state = (t_snake_state){
		.alive = true,
		.length = 1,
		.head = 0,
		.direction = {1, 0},
		.body = {
			[0] = {GRID_WIDTH / 2, GRID_HEIGHT / 2}
		}
	};
	core->views[0] = (t_view){
		.draw = snake_draw,
		.update = snake_update,
		.app_data = &snake_app
	};
	core->current_view = &core->views[0];
}

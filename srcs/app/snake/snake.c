#include "helpers/math.h"
#include "app/snake/snake.h"
#include "app/snake/views/game.h"
#include "app/snake/views/menu.h"

extern void snake_init(t_core *core)
{
	static t_snake_app snake_app;
	t_display *display = core->display;
	uint16_t cell_size = min(
		display->width / GRID_WIDTH, display->height / GRID_HEIGHT
	);

	snake_app.core = core;
	snake_app.draw = (t_snake_draw){
		.cell_size = cell_size,
		.offset_x = (display->width - (GRID_WIDTH * cell_size)) / 2u,
		.offset_y = (display->height - (GRID_HEIGHT * cell_size)) / 2u,
		.game_width = GRID_WIDTH * cell_size,
		.game_height = GRID_HEIGHT * cell_size
	};
	snake_app.game_state = (t_snake_game_state){
		.alive = true,
		.length = 1,
		.next_direction = {1, 0},
		.last_direction = {1, 0},
		.body = {[0] = {GRID_WIDTH / 2, GRID_HEIGHT / 2}}
	};
	snake_app.menu_state = (t_snake_menu_state){
		.placeholder = false
	};
	core->apps[SNAKE_APP] = (t_app){
		.views = {
			[SNAKE_MENU_VIEW] = {
				.draw = snake_menu_draw, .update = snake_menu_update
			},
			[SNAKE_GAME_VIEW] = {
				.draw = snake_game_draw, .update = snake_game_update
			}
		},
		.app_data = &snake_app
	};
	core->apps[SNAKE_APP].current_view
		= &core->apps[SNAKE_APP].views[SNAKE_MENU_VIEW];
	core->current_app = &core->apps[SNAKE_APP];
}

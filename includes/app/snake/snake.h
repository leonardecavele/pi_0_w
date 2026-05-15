#ifndef SNAKE_H
#define SNAKE_H

#include "app/app.h"
#include "display/display.h"
#include "app/snake/display.h"
#include "app/snake/logic.h"

typedef enum e_snake_view
{
	SNAKE_MENU_VIEW = 0,
	SNAKE_GAME_VIEW = 1
}	t_snake_view;

typedef struct s_snake_app
{
	t_core *core;
	t_snake_game_state game_state;
	t_snake_menu_state menu_state;
	t_snake_draw draw;
}	t_snake_app;

void snake_init(t_core *core);

#endif

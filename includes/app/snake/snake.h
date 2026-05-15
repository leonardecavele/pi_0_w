#ifndef SNAKE_H
#define SNAKE_H

#include "app/app.h"
#include "display/display.h"
#include "app/snake/draw.h"
#include "app/snake/logic.h"

typedef enum e_snake_view
{
	SNAKE_GAME_VIEW = 0
}	t_snake_view;

typedef struct s_snake_app
{
	t_core *core;
	t_snake_state state;
	t_snake_display display;
}	t_snake_app;

void snake_init(t_core *core);

#endif

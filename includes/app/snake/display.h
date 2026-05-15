#ifndef SNAKE_DISPLAY_H
#define SNAKE_DISPLAY_H

#include "display/display.h"
#include "app/snake/logic.h"

typedef enum e_snake_colors
{
	SNAKE_BACKGROUND = 0x0000u,
	SNAKE_GAME_BACKGROUND = 0x4BD2,
	SNAKE_BODY_COLOR = 0x76813,
	SNAKE_FRUIT_COLOR = 0x07E0
}	t_snake_colors;

typedef struct s_snake_draw
{
	uint16_t cell_size;
	uint16_t offset_x;
	uint16_t offset_y;
	uint16_t game_width;
	uint16_t game_height;
}	t_snake_draw;

#endif

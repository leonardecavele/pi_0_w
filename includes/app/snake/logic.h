#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

#include "helpers/standard.h"

#define GRID_WIDTH 16
#define GRID_HEIGHT 16

#define SNAKE_MAX_LEN 40
#define SNAKE_SPEED_US (0.2 * 1000000u)

typedef struct s_vec2
{
	int16_t	v1;
	int16_t	v2;
}	t_vec2;

typedef struct s_fruit
{
	t_vec2	pos;
	bool	active;
}	t_fruit;

typedef struct s_snake_game_state
{
	t_vec2		body[SNAKE_MAX_LEN];
	t_vec2		next_direction;
	t_vec2		last_direction;
	uint16_t	head;
	uint16_t	length;
	t_fruit		fruit;
	bool		alive;
}	t_snake_game_state;

typedef struct s_snake_menu_state
{
	bool	placeholder;
}	t_snake_menu_state;

#endif

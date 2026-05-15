#include "drivers/uart.h"
#include "helpers/random.h"
#include "app/snake/snake.h"
#include "app/snake/views/game.h"
#include "system/buttons.h"

static void update_buttons(t_snake_state *state)
{
	if (button_left()) {
		uart_printf(BCM2835_UART0, "snake: LEFT\r\n");
		if (!(state->last_direction.v1 == 1 && state->last_direction.v2 == 0))
			state->next_direction = (t_vec2){-1, 0};
	}
	else if (button_up()) {
		uart_printf(BCM2835_UART0, "snake: UP\r\n");
		if (!(state->last_direction.v1 == 0 && state->last_direction.v2 == 1))
			state->next_direction = (t_vec2){0, -1};
	}
	else if (button_right()) {
		uart_printf(BCM2835_UART0, "snake: RIGHT\r\n");
		if (!(state->last_direction.v1 == -1 && state->last_direction.v2 == 0))
			state->next_direction = (t_vec2){1, 0};
	}
	else if (button_down()) {
		uart_printf(BCM2835_UART0, "snake: DOWN\r\n");
		if (!(state->last_direction.v1 == 0 && state->last_direction.v2 == -1))
			state->next_direction = (t_vec2){0, 1};
	}
}

static bool update_direction(t_snake_state *state, uint32_t elapsed_us)
{
	static uint32_t total_elapsed_us = 0;

	total_elapsed_us += elapsed_us;
	if (total_elapsed_us < SNAKE_SPEED_US)
		return false;
	total_elapsed_us -= SNAKE_SPEED_US;
	t_vec2 head_pos = state->body[state->head];
	t_vec2 new_pos = (t_vec2){
		head_pos.v1 + state->next_direction.v1,
		head_pos.v2 + state->next_direction.v2
	};
	if (new_pos.v1 < 0)
		new_pos.v1 = GRID_WIDTH - 1;
	if (new_pos.v1 >= GRID_WIDTH)
		new_pos.v1 = 0;
	if (new_pos.v2 < 0)
		new_pos.v2 = GRID_HEIGHT - 1;
	if (new_pos.v2 >= GRID_HEIGHT)
		new_pos.v2 = 0;
	state->head = (state->head + 1) % SNAKE_MAX_LEN;
	state->body[state->head] = new_pos;
	state->last_direction = state->next_direction;
	return true;
}

static int16_t on_snake(t_snake_state *state, t_vec2 pos, uint16_t start)
{
	for (int16_t i = start; i < state->length; i++)
	{
		if (
			state->body[
				(state->head - i + SNAKE_MAX_LEN) % SNAKE_MAX_LEN
			].v1 == pos.v1
			&& state->body[
				(state->head - i + SNAKE_MAX_LEN) % SNAKE_MAX_LEN
			].v2 == pos.v2
		)
			return i;
	}
	return -1;
}

static bool on_fruit(t_snake_state *state, t_vec2 pos)
{
	if (
		state->fruit.active
		&& state->fruit.pos.v1 == pos.v1
		&& state->fruit.pos.v2 == pos.v2
	)
		return true;
	return false;
}

static void update_fruit(t_snake_state *state)
{
	while (!state->fruit.active) {
		state->fruit.pos.v1 = random_u32() % GRID_WIDTH;
		state->fruit.pos.v2 = random_u32() % GRID_HEIGHT;
		if (on_snake(state, state->fruit.pos, 0) == -1)
			state->fruit.active = true;
	}
}

static void update_collision(t_snake_state *state)
{
	if (on_fruit(state, state->body[state->head])) {
		state->fruit.active = false;
		state->length = (state->length % SNAKE_MAX_LEN) + 1;
	}
	if (on_snake(state, state->body[state->head], 1) != -1) {
		state->next_direction = (t_vec2){0, 0};
		state->last_direction = (t_vec2){0, 0};
		state->alive = false;
		uart_printf(BCM2835_UART0, "snake: DEAD\r\n");
	}
}

extern void snake_game_update(void *app_data)
{
	t_snake_app *snake_app = app_data;

	if (!snake_app->state.alive)
		return ;
	update_buttons(&snake_app->state);
	if (update_direction(&snake_app->state, snake_app->core->dt))
		update_collision(&snake_app->state);
	update_fruit(&snake_app->state);
}

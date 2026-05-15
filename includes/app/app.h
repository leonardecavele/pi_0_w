#ifndef APP_H
#define APP_H

#include "display/display.h"

#define LEN_APP 100
#define LEN_VIEW 10

typedef enum e_app_index
{
	SNAKE_APP = 0
} t_app_index;

typedef struct s_view
{
	void (*draw)(void *app_data);
	void (*update)(void *app_data);
} t_view;

typedef struct s_app
{
	t_view *current_view;
	t_view views[LEN_VIEW];
	void *app_data;
} t_app;

typedef struct s_core
{
	uint32_t dt;
	t_display *display;
	t_app *current_app;
	t_app apps[LEN_APP];
} t_core;

#endif

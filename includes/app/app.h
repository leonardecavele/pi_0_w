#ifndef APP_H
#define APP_H

#include "display/display.h"

#define LEN_VIEW 10

typedef struct s_view
{
	void (*draw)(void *app_data);
	void (*update)(void *app_data);
	void *app_data;
} t_view;

typedef struct s_core
{
	uint32_t dt;
	t_display *display;
	t_view *current_view;
	t_view views[LEN_VIEW];
} t_core;

#endif

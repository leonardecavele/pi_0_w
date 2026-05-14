#ifndef APP_H
#define APP_H

#define LEN_VIEW 10

/* app_data may vary with different programs */

typedef struct s_view {
	void (*display)(void *app_data);
	void (*update)(void *app_data);
} t_view;

typedef struct s_app {
	uint32_t dt;
	t_view *current_view;
	t_view views[LEN_VIEW];
} t_app;

#endif

#ifndef DISPLAY_H
# define DISPLAY_H

# include "standard.h"
# include "gpio.h"
# include "spi.h"

# define DISPLAY_DC_GPIO   27u
# define DISPLAY_RST_GPIO  22u

typedef enum e_display_mode
{
	DISPLAY_COMMAND = 0,
	DISPLAY_BYTES = 1
}	t_display_mode;

void	display_init(void);
void	display_reset(void);
void	display_set_mode(t_display_mode mode);

#endif

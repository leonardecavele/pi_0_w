#ifndef SNAKE_H
#define SNAKE_H

#include "display/display.h"

#define TARGET_FPS 60u
#define FRAME_US (1000000u / TARGET_FPS)

void snake(t_display *display);

#endif

#ifndef TIME_H
#define TIME_H

#include "standard.h"
#include "bcm2835.h"

#define ST_REG(a) (BCM2835_ST + (uint32_t)(a))

typedef enum e_st_offset
{
	ST_CS  = 0x00u,
	ST_CLO = 0x04u,
	ST_CHI = 0x08u
}	t_st_offset;

uint64_t get_time_us(void);
uint32_t get_time_ms(void);
void usleep(uint32_t usec);
void msleep(uint32_t msec);

#endif

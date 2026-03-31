#include "bcm2835.h"
#include "address.h"
#include "time.h"

uint64_t	get_time_us(void)
{
	uint32_t	hi;
	uint32_t	lo;
	uint32_t	hi_check;

	hi = REG4B(ST_REG(ST_CHI));
	lo = REG4B(ST_REG(ST_CLO));
	hi_check = REG4B(ST_REG(ST_CHI));
	if (hi != hi_check)
	{
		hi = hi_check;
		lo = REG4B(ST_REG(ST_CLO));
	}
	return (((uint64_t)hi << 32) | (uint64_t)lo);
}

uint32_t	get_time_ms(void)
{
	return ((uint32_t)(get_time_us() / 1000u));
}

void	usleep(uint32_t usec)
{
	uint32_t	start;

	start = get_time_us();
	while ((get_time_us() - start) < (uint32_t)usec)
		;
}

void	msleep(uint32_t msec)
{
	usleep(msec * 1000u);
}

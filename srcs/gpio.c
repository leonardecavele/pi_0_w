#include "gpio.h"

/* WIP before real timer set-up */
static void gpio_delay(uint32_t n)
{
	volatile uint32_t	i;

	i = 0u;
	while (i < n)
		i++;
}

extern void gpio_set_func(uint32_t gpio, t_gpio_funcsel func)
{
	uint32_t	reg;
	uint32_t	shift;
	uint32_t	mask;
	uint32_t	val;

	if (gpio > GPIO_MAX)
		return ;
	reg = REG4B(GPIO_FSEL(gpio));
	shift = GPIO_FSEL_SHIFT(gpio);
	mask = 0x7u << shift;
	val = ((uint32_t)func << shift);
	reg &= ~mask;
	reg |= val;
	REG4B(GPIO_FSEL(gpio)) = reg;
}

extern void gpio_write(uint32_t gpio, bool value)
{
	if (gpio > GPIO_MAX)
		return ;
	if (value)
		REG4B(GPIO_SET(gpio)) = GPIO_MASK(gpio);
	else
		REG4B(GPIO_CLR(gpio)) = GPIO_MASK(gpio);
}

extern bool gpio_read(uint32_t gpio)
{
	if (gpio > GPIO_MAX)
		return (false);
	return (GPIO_GET_BIT(gpio) != 0u);
}

extern void gpio_set_pull(uint32_t gpio, t_gpio_pull pull)
{
	if (gpio > GPIO_MAX)
		return ;
	REG4B(BCM2835_GPIO + GPPUD) = ((uint32_t)pull << PUD_SHIFT) & PUD_MASK;
	gpio_delay(150u);
	REG4B(GPIO_PUDCLK(gpio)) = GPIO_MASK(gpio);
	gpio_delay(150u);
	REG4B(BCM2835_GPIO + GPPUD) = 0u;
	REG4B(GPIO_PUDCLK(gpio)) = 0u;
}

extern void gpio_enable_falling(uint32_t gpio)
{
    if (gpio > GPIO_MAX)
        return;
    REG4B(GPIO_FEN(gpio)) |= GPIO_MASK(gpio);
}

extern void gpio_disable_falling(uint32_t gpio)
{
    if (gpio > GPIO_MAX)
        return;
    REG4B(GPIO_FEN(gpio)) &= ~GPIO_MASK(gpio);
}

extern void gpio_enable_rising(uint32_t gpio)
{
    if (gpio > GPIO_MAX)
        return;
    REG4B(GPIO_REN(gpio)) |= GPIO_MASK(gpio);
}

extern void gpio_disable_rising(uint32_t gpio)
{
    if (gpio > GPIO_MAX)
        return;
    REG4B(GPIO_REN(gpio)) &= ~GPIO_MASK(gpio);
}

extern bool gpio_event_pending(uint32_t gpio)
{
    if (gpio > GPIO_MAX)
        return (false);
    return ((REG4B(GPIO_EDS(gpio)) & GPIO_MASK(gpio)) != 0u);
}

extern void gpio_event_clear(uint32_t gpio)
{
    if (gpio > GPIO_MAX)
        return;
    REG4B(GPIO_EDS(gpio)) = GPIO_MASK(gpio);
}

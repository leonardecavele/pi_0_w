#ifndef GPIO_H
#define GPIO_H

#include "bcm2835.h"

/* get function select address of gpio 'a' */
#define GPIO_FSEL(a)	(BCM2835_GPIO + ((uint32_t)(a) / 10u) * 4u)

/* get bit shift in function select register of gpio 'a' */
#define GPIO_FSEL_SHIFT(a)	(((uint32_t)(a) % 10u) * 3u)

/* get set address of gpio 'a' */
#define GPIO_SET(a)	(BCM2835_GPIO + 0x1cu + ((uint32_t)(a) / 32u) * 4u)

/* get clear address of gpio 'a' */
#define GPIO_CLR(a)	(BCM2835_GPIO + 0x28u + ((uint32_t)(a) / 32u) * 4u)

/* get level address of gpio 'a' */
#define GPIO_LEV(a)	(BCM2835_GPIO + 0x34u + ((uint32_t)(a) / 32u) * 4u)

/* get event detect status address of gpio 'a' */
#define GPIO_EDS(a)	(BCM2835_GPIO + 0x40u + ((uint32_t)(a) / 32u) * 4u)

/* get rising edge detect address of gpio 'a' */
#define GPIO_REN(a)	(BCM2835_GPIO + 0x4cu + ((uint32_t)(a) / 32u) * 4u)

/* get falling edge detect address of gpio 'a' */
#define GPIO_FEN(a)	(BCM2835_GPIO + 0x58u + ((uint32_t)(a) / 32u) * 4u)

/* get high detect address of gpio 'a' */
#define GPIO_HEN(a)	(BCM2835_GPIO + 0x64u + ((uint32_t)(a) / 32u) * 4u)

/* get low detect address of gpio 'a' */
#define GPIO_LEN(a)	(BCM2835_GPIO + 0x70u + ((uint32_t)(a) / 32u) * 4u)

/* get async rising edge detect address of gpio 'a' */
#define GPIO_AREN(a)	(BCM2835_GPIO + 0x7cu + ((uint32_t)(a) / 32u) * 4u)

/* get async falling edge detect address of gpio 'a' */
#define GPIO_AFEN(a)	(BCM2835_GPIO + 0x88u + ((uint32_t)(a) / 32u) * 4u)

/* get pull-up/down clock address of gpio 'a' */
#define GPIO_PUDCLK(a)	(BCM2835_GPIO + 0x98u + ((uint32_t)(a) / 32u) * 4u)

/* get bit mask of gpio 'a' */
#define GPIO_MASK(a)	(1u << ((uint32_t)(a) % 32u))

/* get level bit of gpio 'a' */
#define GPIO_GET_BIT(a)	((REG4B(GPIO_LEV((a))) >> ((uint32_t)(a) % 32u)) & 1u)

/* bcm2835 exposes gpio 0 to 53 */
#define GPIO_MAX	53u

typedef enum e_gpio_offset {
	GPFSEL0 = 0x00u,
	GPFSEL1 = 0x04u,
	GPFSEL2 = 0x08u,
	GPFSEL3 = 0x0cu,
	GPFSEL4 = 0x10u,
	GPFSEL5 = 0x14u,
	GPSET0 = 0x1cu,
	GPSET1 = 0x20u,
	GPCLR0 = 0x28u,
	GPCLR1 = 0x2cu,
	GPLEV0 = 0x34u,
	GPLEV1 = 0x38u,
	GPEDS0 = 0x40u,
	GPEDS1 = 0x44u,
	GPREN0 = 0x4cu,
	GPREN1 = 0x50u,
	GPFEN0 = 0x58u,
	GPFEN1 = 0x5cu,
	GPHEN0 = 0x64u,
	GPHEN1 = 0x68u,
	GPLEN0 = 0x70u,
	GPLEN1 = 0x74u,
	GPAREN0 = 0x7cu,
	GPAREN1 = 0x80u,
	GPAFEN0 = 0x88u,
	GPAFEN1 = 0x8cu,
	GPPUD = 0x94u,
	GPPUDCLK0 = 0x98u,
	GPPUDCLK1 = 0x9cu
} t_gpio_offset;

typedef enum e_gpio_funcsel {
	GPIO_INPUT = 0u,
	GPIO_OUTPUT = 1u,
	GPIO_ALT5 = 2u,
	GPIO_ALT4 = 3u,
	GPIO_ALT0 = 4u,
	GPIO_ALT1 = 5u,
	GPIO_ALT2 = 6u,
	GPIO_ALT3 = 7u
} t_gpio_funcsel;

typedef enum e_gpio_pull {
	GPIO_PULL_OFF = 0u,
	GPIO_PULL_DOWN = 1u,
	GPIO_PULL_UP = 2u
} t_gpio_pull;

typedef enum e_gpio_shift {
	PUD_SHIFT = 0
} t_gpio_shift;

typedef enum e_gpio_mask {
	PUD_MASK = 0x00000003u
} t_gpio_mask;

/* set-up */
void gpio_set_func(uint32_t gpio, t_gpio_funcsel func);
void gpio_set_pull(uint32_t gpio, t_gpio_pull pull);
/* interract */
void gpio_write(uint32_t gpio, bool value);
bool gpio_read(uint32_t gpio);
/* interrupts */
void gpio_enable_falling(uint32_t gpio);
void gpio_disable_falling(uint32_t gpio);
void gpio_enable_rising(uint32_t gpio);
void gpio_disable_rising(uint32_t gpio);
bool gpio_event_pending(uint32_t gpio);
void gpio_event_clear(uint32_t gpio);

#endif

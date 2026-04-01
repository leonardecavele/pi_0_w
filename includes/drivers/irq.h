#ifndef IRQ_H
#define IRQ_H

#include "standard.h"
#include "bcm2835.h"

#define IRQ_COUNT 72u
#define IRQ_GPIO_BANK0 49u
#define IRQ_GPIO_BANK0_BIT (1u << (IRQ_GPIO_BANK0 - 32u))

typedef void (*t_irq_handler)(void *ctx);

typedef enum e_irq_reg
{
	IRQ_BASIC_PENDING = 0x200u,
	IRQ_PENDING_1     = 0x204u,
	IRQ_PENDING_2     = 0x208u,
	IRQ_FIQ_CTRL      = 0x20cu,
	IRQ_ENABLE_1      = 0x210u,
	IRQ_ENABLE_2      = 0x214u,
	IRQ_ENABLE_BASIC  = 0x218u,
	IRQ_DISABLE_1     = 0x21cu,
	IRQ_DISABLE_2     = 0x220u,
	IRQ_DISABLE_BASIC = 0x224u
} t_irq_reg;

/* low-level asm */
void disable_irq(void);
void enable_irq(void);
void vector_init_irq(void);
void controller_reset_irq(void);
void controller_enable_irq(uint32_t irq);
void controller_disable_irq(uint32_t irq);
uint32_t controller_pending_1_irq(void);
uint32_t controller_pending_2_irq(void);
uint32_t controller_basic_pending_irq(void);

/* C driver */
void irq_init(void);
int irq_register(uint32_t irq, t_irq_handler fn, void *ctx);
void irq_unregister(uint32_t irq);
void irq_enable_line(uint32_t irq);
void irq_disable_line(uint32_t irq);
void handle_irq(void);

#endif

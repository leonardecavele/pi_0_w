#ifndef IRQ_H
#define IRQ_H

#include "standard.h"
#include "bcm2835.h"

#define IRQ_BASIC_PENDING 0x200u
#define IRQ_PENDING_1 0x204u
#define IRQ_PENDING_2 0x208u
#define IRQ_ENABLE_1 0x210u
#define IRQ_ENABLE_2 0x214u
#define IRQ_ENABLE_BASIC 0x218u
#define IRQ_DISABLE_1 0x21cu
#define IRQ_DISABLE_2 0x220u
#define IRQ_DISABLE_BASIC 0x224u

#define IRQ_GPIO_BANK0 49u
#define IRQ_GPIO_BANK0_BIT (1u << (IRQ_GPIO_BANK0 - 32u))

extern volatile uint32_t g_button_event;

void irq_init_button(void);
void irq_handler_c(void);
void irq_enable(void);
void wait_for_interrupt(void);

#endif

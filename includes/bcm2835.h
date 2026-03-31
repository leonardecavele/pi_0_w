#ifndef BCM2835_H
#define BCM2835_H

#include "standard.h"
#include "address.h"

/* peripheral base (ARM physical address) */
#define BCM2835_PERI_BASE UADDR(0x20000000u)

/* base addresses */
#define BCM2835_GPIO UADDR(BCM2835_PERI_BASE + 0x00200000u)
#define BCM2835_UART0 UADDR(BCM2835_PERI_BASE + 0x00201000u)
#define BCM2835_IRQ UADDR(BCM2835_PERI_BASE + 0x0000b200u)
#define BCM2835_SPI0 UADDR(BCM2835_PERI_BASE + 0x00204000u)
#define BCM2835_ST UADDR(BCM2835_PERI_BASE + 0x00003000u)

#endif

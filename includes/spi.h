#ifndef SPI_H
#define SPI_H

#include "gpio.h"

#define SPI0_CE0_GPIO  8u
#define SPI0_MOSI_GPIO 10u
#define SPI0_SCLK_GPIO 11u

/* register access */
#define SPI0_REG(a) (BCM2835_SPI0 + (uint32_t)(a))

typedef enum e_spi0_offset
{
	 SPI0_CS   = 0x00u,
	 SPI0_FIFO = 0x04u,
	 SPI0_CLK  = 0x08u,
	 SPI0_DLEN = 0x0cu,
	 SPI0_LTOH = 0x10u,
	 SPI0_DC   = 0x14u
}	t_spi0_offset;

/*
** SPI0_CS register bits
*/
typedef enum e_spi_cs_shift
{
	 SPI_CS_SHIFT_CS      = 0,
	 SPI_CS_SHIFT_CPHA    = 2,
	 SPI_CS_SHIFT_CPOL    = 3,
	 SPI_CS_SHIFT_CLEAR   = 4,
	 SPI_CS_SHIFT_CSPOL   = 6,
	 SPI_CS_SHIFT_TA      = 7,
	 SPI_CS_SHIFT_DMAEN   = 8,
	 SPI_CS_SHIFT_INTD    = 9,
	 SPI_CS_SHIFT_INTR    = 10,
	 SPI_CS_SHIFT_ADCS    = 11,
	 SPI_CS_SHIFT_REN     = 12,
	 SPI_CS_SHIFT_LEN     = 13,
	 SPI_CS_SHIFT_LMONO   = 14,
	 SPI_CS_SHIFT_TE_EN   = 15,
	 SPI_CS_SHIFT_DONE    = 16,
	 SPI_CS_SHIFT_RXD     = 17,
	 SPI_CS_SHIFT_TXD     = 18,
	 SPI_CS_SHIFT_RXR     = 19,
	 SPI_CS_SHIFT_RXF     = 20,
	 SPI_CS_SHIFT_CSPOL0  = 21,
	 SPI_CS_SHIFT_CSPOL1  = 22,
	 SPI_CS_SHIFT_CSPOL2  = 23,
	 SPI_CS_SHIFT_DMA_LEN = 24,
	 SPI_CS_SHIFT_LEN_LONG = 25
}	t_spi_cs_shift;

typedef enum e_spi_cs_mask
{
	 SPI_CS_MASK_CS       = 0x00000003u,
	 SPI_CS_MASK_CLEAR    = 0x00000030u,
	 SPI_CS_MASK_CPHA     = 0x00000004u,
	 SPI_CS_MASK_CPOL     = 0x00000008u,
	 SPI_CS_MASK_CSPOL    = 0x00000040u,
	 SPI_CS_MASK_TA       = 0x00000080u,
	 SPI_CS_MASK_DMAEN    = 0x00000100u,
	 SPI_CS_MASK_INTD     = 0x00000200u,
	 SPI_CS_MASK_INTR     = 0x00000400u,
	 SPI_CS_MASK_ADCS     = 0x00000800u,
	 SPI_CS_MASK_REN      = 0x00001000u,
	 SPI_CS_MASK_LEN      = 0x00002000u,
	 SPI_CS_MASK_LMONO    = 0x00004000u,
	 SPI_CS_MASK_TE_EN    = 0x00008000u,
	 SPI_CS_MASK_DONE     = 0x00010000u,
	 SPI_CS_MASK_RXD      = 0x00020000u,
	 SPI_CS_MASK_TXD      = 0x00040000u,
	 SPI_CS_MASK_RXR      = 0x00080000u,
	 SPI_CS_MASK_RXF      = 0x00100000u,
	 SPI_CS_MASK_CSPOL0   = 0x00200000u,
	 SPI_CS_MASK_CSPOL1   = 0x00400000u,
	 SPI_CS_MASK_CSPOL2   = 0x00800000u,
	 SPI_CS_MASK_DMA_LEN  = 0x01000000u,
	 SPI_CS_MASK_LEN_LONG = 0x02000000u
}	t_spi_cs_mask;

typedef enum e_spi_chip_select
{
	 SPI_CS_0 = 0u,
	 SPI_CS_1 = 1u,
	 SPI_CS_2 = 2u
}	t_spi_chip_select;

typedef enum e_spi_clear
{
	 SPI_CLEAR_RX = 0x01u,
	 SPI_CLEAR_TX = 0x02u,
	 SPI_CLEAR_RX_TX = 0x03u
}	t_spi_clear;

typedef enum e_spi_mode
{
	 SPI_MODE0 = 0u,
	 SPI_MODE1 = SPI_CS_MASK_CPHA,
	 SPI_MODE2 = SPI_CS_MASK_CPOL,
	 SPI_MODE3 = SPI_CS_MASK_CPOL | SPI_CS_MASK_CPHA
}	t_spi_mode;

void	spi_init(uint16_t clk_div, t_spi_mode mode);
void	spi_begin(void);
void	spi_end(void);
void	spi_write(uint8_t byte);

#endif

#include "spi.h"

static void	spi_flush_rx(void)
{
	while ((REG4B(SPI0_REG(SPI0_CS)) & SPI_CS_MASK_RXD) != 0u)
		(void)REG4B(SPI0_REG(SPI0_FIFO));
}

extern void	spi_init(uint16_t clk_div, t_spi_mode mode)
{
	uint32_t	cs;

	gpio_set_func(SPI0_CE0_GPIO, GPIO_ALT0);
	gpio_set_func(SPI0_MOSI_GPIO, GPIO_ALT0);
	gpio_set_func(SPI0_SCLK_GPIO, GPIO_ALT0);

	gpio_set_pull(SPI0_CE0_GPIO, GPIO_PULL_OFF);
	gpio_set_pull(SPI0_MOSI_GPIO, GPIO_PULL_OFF);
	gpio_set_pull(SPI0_SCLK_GPIO, GPIO_PULL_OFF);

	cs = 0u;
	cs |= ((uint32_t)SPI_CLEAR_RX_TX << SPI_CS_SHIFT_CLEAR);
	cs |= (uint32_t)SPI_CS_0;
	cs |= (uint32_t)mode;
	REG4B(SPI0_REG(SPI0_CS)) = cs;

	if (clk_div == 0u)
		clk_div = 2u;
	REG4B(SPI0_REG(SPI0_CLK)) = (uint32_t)clk_div;

	spi_flush_rx();
}

extern void	spi_begin(void)
{
	uint32_t	cs;

	cs = REG4B(SPI0_REG(SPI0_CS));
	cs &= ~(SPI_CS_MASK_CLEAR | SPI_CS_MASK_CS);
	cs |= ((uint32_t)SPI_CLEAR_RX_TX << SPI_CS_SHIFT_CLEAR);
	cs |= (uint32_t)SPI_CS_0;
	cs |= SPI_CS_MASK_TA;
	REG4B(SPI0_REG(SPI0_CS)) = cs;
}

extern void	spi_end(void)
{
	while ((REG4B(SPI0_REG(SPI0_CS)) & SPI_CS_MASK_DONE) == 0u)
		;
	REG4B(SPI0_REG(SPI0_CS)) &= ~SPI_CS_MASK_TA;
	spi_flush_rx();
}

extern void	spi_write(uint8_t byte)
{
	while ((REG4B(SPI0_REG(SPI0_CS)) & SPI_CS_MASK_TXD) == 0u)
		;
	REG4B(SPI0_REG(SPI0_FIFO)) = (uint32_t)byte;
	while ((REG4B(SPI0_REG(SPI0_CS)) & SPI_CS_MASK_DONE) == 0u)
		;
	spi_flush_rx();
}

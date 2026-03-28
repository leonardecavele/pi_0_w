#include "standard.h"
#include "uart.h"
#include "gpio.h"
#include "command.h"

static t_command_status	execute_cmd(const char buffer[BUFFER_SIZE])
{
	if (!strcmp(buffer, "exit")) {
		return (EXIT);
	}
	else if (!strcmp(buffer, "turn on red")) {
		gpio_write(22u, 1);
		return (FOUND);
	}
	else if (!strcmp(buffer, "turn on blue")) {
		gpio_write(17u, 1);
		return (FOUND);
	}
	else if (!strcmp(buffer, "turn on green")) {
		gpio_write(27u, 1);
		return (FOUND);
	}
	else if (!strcmp(buffer, "turn off red")) {
		gpio_write(22u, 0);
		return (FOUND);
	}
	else if (!strcmp(buffer, "turn off blue")) {
		gpio_write(17u, 0);
		return (FOUND);
	}
	else if (!strcmp(buffer, "turn off green")) {
		gpio_write(27u, 0);
		return (FOUND);
	}
	else if (!strcmp(buffer, "turn on all")) {
		gpio_write(22u, 1);
		gpio_write(17u, 1);
		gpio_write(27u, 1);
		return (FOUND);
	}
	else if (!strcmp(buffer, "turn off all")) {
		gpio_write(22u, 0);
		gpio_write(17u, 0);
		gpio_write(27u, 0);
		return (FOUND);
	}
	return (UNKNOWN);
}

extern void	wait_cmd(uintptr_t t)
{
	char				buffer[BUFFER_SIZE];
	uint32_t			index;
	char				c;
	t_command_status	s;

	index = 0;
	uart_putstr(t, "> ");
	while (1) {
		c = uart_getc(t);
		if ((c == '\b' || c == 127) && index > 0) {
			index--;
			uart_putstr(t, "\b \b");
		}
		else if (c == '\r' || c == '\n') {
			uart_putstr(t, "\r\n");
			buffer[index] = 0;
			if (index == 0) {
				uart_putstr(t, "> ");
				continue;
			}
			s = execute_cmd(buffer);
			index = 0;
			if (s == EXIT)
				return;
			if (s == UNKNOWN)
				uart_putstr(t, "unknown command\r\n");
			uart_putstr(t, "> ");
		}
		else if (index < BUFFER_SIZE - 1) {
			buffer[index++] = c;
			uart_putc(t, c);
		}
	}
}

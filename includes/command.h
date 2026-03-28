#ifndef COMMAND_H
#define COMMAND_H

#define BUFFER_SIZE 1024

typedef enum e_command_status {
	FOUND,
	UNKNOWN,
	EXIT
}	t_command_status;

void wait_cmd(uintptr_t t);

#endif

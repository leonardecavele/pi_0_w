# structure
NAME = kernel
BUILD = build
SRCS = srcs
OUT = boot
INCLUDES = includes

# flags
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

CPU_FLAGS = -mcpu=arm1176jzf-s -marm
C_FLAGS = -I $(INCLUDES) \
		  $(CPU_FLAGS) \
		  -ffreestanding -nostdlib -nostartfiles \
		  -fno-omit-frame-pointer -fno-unwind-tables \
		  -fno-asynchronous-unwind-tables -fno-builtin-memset \
		  -fno-builtin-memcpy
S_FLAGS = $(CPU_FLAGS)
LD_FLAGS = -Wl,-z,max-page-size=4096 -Wl,-Map,$(MAP)

# files
S_SRCS = \
		 boot.s \
		 standard.s \
		 irq.s

C_SRCS = \
		 kmain.c \
		 uart.c \
		 gpio.c \
		 standard.c \
		 command.c

LD_SCRIPT = kernel.ld
IMG = $(OUT)/$(NAME).img
TMP = $(IMG).tmp
MAP = $(NAME).map
ELF = $(BUILD)/$(NAME).elf

S_OBJS = $(S_SRCS:%.s=$(BUILD)/s_%.o)
C_OBJS = $(C_SRCS:%.c=$(BUILD)/c_%.o)

# rules
all: $(IMG)

$(IMG): $(C_OBJS) $(S_OBJS) $(LD_SCRIPT)
	$(CC) -T $(LD_SCRIPT) -o $(ELF) $(S_OBJS) $(C_OBJS) $(CPU_FLAGS) -nostdlib -lgcc $(LD_FLAGS)
	$(OBJCOPY) $(ELF) -O binary $(IMG)
	dd if=$(IMG) of=$(TMP) bs=512 conv=sync && mv $(TMP) $(IMG)

$(BUILD)/s_%.o: $(SRCS)/%.s
	mkdir -p $(BUILD)
	$(CC) -c $< -o $@ $(S_FLAGS)

$(BUILD)/c_%.o: $(SRCS)/%.c
	mkdir -p $(BUILD)
	$(CC) -c $< -o $@ $(C_FLAGS)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(IMG) $(MAP)

re: fclean all

# miscellaneous
.PHONY: all clean fclean re

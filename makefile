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
		 system/boot.s \
		 system/interrupts.s \
		 drivers/irq.s

C_SRCS = \
		 kmain.c \
		 system/mapping.c \
		 system/buttons.c \
		 app/snake/snake.c \
		 app/snake/views/game/update.c \
		 app/snake/views/game/draw.c \
		 display/display.c \
		 display/draw.c \
		 drivers/uart.c \
		 drivers/gpio.c \
		 drivers/spi.c \
		 drivers/irq.c \
		 drivers/st7735.c \
		 helpers/standard.c \
		 helpers/time.c \
		 helpers/math.c \
		 helpers/random.c

LD_SCRIPT = kernel.ld
IMG = $(OUT)/$(NAME).img
TMP = $(IMG).tmp
MAP = $(NAME).map
ELF = $(BUILD)/$(NAME).elf

S_OBJS = $(S_SRCS:%.s=$(BUILD)/%.s.o)
C_OBJS = $(C_SRCS:%.c=$(BUILD)/%.c.o)

# rules
all: $(IMG)

$(IMG): $(C_OBJS) $(S_OBJS) $(LD_SCRIPT)
	$(CC) -T $(LD_SCRIPT) -o $(ELF) $(S_OBJS) $(C_OBJS) $(CPU_FLAGS) -nostdlib -lgcc $(LD_FLAGS)
	$(OBJCOPY) $(ELF) -O binary $(IMG)
	dd if=$(IMG) of=$(TMP) bs=512 conv=sync && mv $(TMP) $(IMG)

$(BUILD)/%.s.o: $(SRCS)/%.s
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(S_FLAGS)

$(BUILD)/%.c.o: $(SRCS)/%.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(C_FLAGS)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(IMG) $(MAP)

re: fclean all

# miscellaneous
.PHONY: all clean fclean re

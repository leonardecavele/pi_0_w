ENTRY(_start)

SECTIONS
{
	/* kernel address */
	. = 0x8000;

	.text ALIGN(16) : {
	  *(.text*)
	}

	.rodata ALIGN(16) : {
	  *(.rodata*)
	}

	.data ALIGN(16) : {
	  *(.data*)
	}

	.bss (NOLOAD) : ALIGN(16) {
	  __bss_start = .;
	  *(.bss*)
	  *(COMMON)
	  __bss_end = .;
	}

	.stack (NOLOAD) : ALIGN(16) {
	  __stack_bottom = .;
	  /* 64 KiB */
	  . = . + 0x10000;
	  __stack_top = .;
	}

	.irq_stack (NOLOAD) : ALIGN(16) {
	  __irq_stack_bottom = .;
	  /* 4 KiB */
	  . = . + 0x1000;
	  
	  __irq_stack_top = .;
	}
}

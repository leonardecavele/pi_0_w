.section .text

.global disable_irq
.global enable_irq

.global cpu_use_low_vectors_vbar
.global cpu_set_vbar
.global cpu_isb
.global vector_init_irq

.global controller_reset_irq
.global controller_enable_irq
.global controller_disable_irq
.global controller_pending_1_irq
.global controller_pending_2_irq
.global controller_basic_pending_irq

disable_irq:
	cpsid if
	bx lr

enable_irq:
	mrs r0, cpsr
	bic r0, r0, #0x80
	msr cpsr_c, r0
	bx lr

cpu_use_low_vectors_vbar:
	mrc p15, 0, r0, c1, c0, 0
	bic r0, r0, #0x2000
	mcr p15, 0, r0, c1, c0, 0
	bx lr

cpu_set_vbar:
	mcr p15, 0, r0, c12, c0, 0
	bx lr

cpu_isb:
	mov r0, #0
	mcr p15, 0, r0, c7, c5, 4
	bx lr

vector_init_irq:
	bl cpu_use_low_vectors_vbar
	ldr r0, =__exception_vectors
	bl cpu_set_vbar
	bl cpu_isb
	bx lr

controller_reset_irq:
	ldr r0, =0x2000b21c
	ldr r1, =0xffffffff
	str r1, [r0]

	ldr r0, =0x2000b220
	str r1, [r0]

	ldr r0, =0x2000b224
	str r1, [r0]

	ldr r0, =0x2000b20c
	mov r1, #0
	str r1, [r0]

	bx lr

controller_enable_irq:
	/* r0 = irq number */

	cmp r0, #32
	blt enable_1_irq

	cmp r0, #64
	blt enable_2_irq

	cmp r0, #72
	bhs ctrl_ret_irq

	b enable_basic_irq

enable_1_irq:
	ldr r1, =0x2000b210
	mov r2, #1
	lsl r2, r2, r0
	str r2, [r1]
	bx lr

enable_2_irq:
	sub r0, r0, #32
	ldr r1, =0x2000b214
	mov r2, #1
	lsl r2, r2, r0
	str r2, [r1]
	bx lr

enable_basic_irq:
	sub r0, r0, #64
	ldr r1, =0x2000b218
	mov r2, #1
	lsl r2, r2, r0
	str r2, [r1]
	bx lr

controller_disable_irq:
	/* r0 = irq number */

	cmp r0, #32
	blt disable_1_irq

	cmp r0, #64
	blt disable_2_irq

	cmp r0, #72
	bhs ctrl_ret_irq

	b disable_basic_irq

disable_1_irq:
	ldr r1, =0x2000b21c
	mov r2, #1
	lsl r2, r2, r0
	str r2, [r1]
	bx lr

disable_2_irq:
	sub r0, r0, #32
	ldr r1, =0x2000b220
	mov r2, #1
	lsl r2, r2, r0
	str r2, [r1]
	bx lr

disable_basic_irq:
	sub r0, r0, #64
	ldr r1, =0x2000b224
	mov r2, #1
	lsl r2, r2, r0
	str r2, [r1]
	bx lr

controller_pending_1_irq:
	ldr r0, =0x2000b204
	ldr r0, [r0]
	bx lr

controller_pending_2_irq:
	ldr r0, =0x2000b208
	ldr r0, [r0]
	bx lr

controller_basic_pending_irq:
	ldr r0, =0x2000b200
	ldr r0, [r0]
	bx lr

ctrl_ret_irq:
	bx lr

.extern irq_disable
.extern cpu_use_low_vectors_vbar
.extern cpu_set_vbar
.extern cpu_isb
.extern cpu_set_mode_irq
.extern cpu_set_mode_svc

.section .text
.global _start

.align 5
vectors:
	b _start    // reset
	b .         // undefined instruction
	b .         // swi / svc
	b .         // prefetch abort
	b .         // data abort
	b .         // reserved
	b irq		// irq
	b .         // fiq

irq:
    stmfd sp!, {r0-r3, r12, lr}
    bl handle_irq
    ldmfd sp!, {r0-r3, r12, lr}
    subs pc, lr, #4

_start:
	bl irq_disable

	bl cpu_use_low_vectors_vbar

	ldr r0, =vectors
	bl cpu_set_vbar

	bl cpu_isb

	/* switch to IRQ mode */
	mrs r0, cpsr
	bic r0, r0, #0x1f
	orr r0, r0, #0x12
	msr cpsr_c, r0

	/* set IRQ stack */
	ldr sp, =__irq_stack_top

	/* switch to SVC mode */
	mrs r0, cpsr
	bic r0, r0, #0x1f
	orr r0, r0, #0x13
	msr cpsr_c, r0

	/* set stack */
	ldr sp, =__stack_top

	ldr r0, =__bss_start
	ldr r1, =__bss_end
	mov r2, #0

bss_loop:
	/* write 0 then increase pointer by 1 while in bss */
	cmp r0, r1
	bhs bss_done
	strb r2, [r0], #1
	b bss_loop

bss_done:
	/* branch to kernel main */
	bl kmain

cpu_hang:
	b cpu_hang

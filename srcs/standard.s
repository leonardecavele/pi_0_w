.section .text
.global sleep

sleep:
	wfi
	bx lr

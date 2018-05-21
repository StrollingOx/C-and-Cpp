.global main
.arm

.EQU	PIOB_PER,		0xFFFFF400 
.EQU	PIOB_OER,		0xFFFFF410 	
.EQU	PIOB_CODR,		0xFFFFF434 
.EQU	PIOB_SODR,		0xFFFFF430 
.EQU    LED,            (1<<8)

init:
	LDR	R0, =PIOB_PER 
	LDR     R1, =LED 
	STR     R1, [R0]

	LDR	R0, =PIOB_OER
	LDR     R1, =LED 
	STR     R1, [R0]

	BX LR

main:
	BL	init	
	B	main_prg

main_prg:
	BL 	on	
	BL 	off
	B	main_prg



on:
	STMDB	sp!, {LR}
	LDR	R0, =PIOB_CODR
	LDR     R1, =LED
	STR     R1, [R0]
	LDR 	R2, =10000
	B	wait


off:
	STMDB	sp!, {LR}
	LDR	R0, =PIOB_SODR
	LDR     R1, =LED
	STR     R1, [R0]
	LDR 	R2, =10000
	B	wait

wait:
	LDR 	R3, =5
	BL	waitwait_s
	SUBS	R2, #1
	BNE wait
	LDMIA	sp!, {LR}
	BX 	LR

waitwait_s:
	STMDB	sp!, {LR}
waitwait:
	SUBS	R3, #1
	BNE waitwait
	LDMIA	sp!, {LR}
	BX LR

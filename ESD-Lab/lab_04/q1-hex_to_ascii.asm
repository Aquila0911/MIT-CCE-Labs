	AREA RESET, DATA, READONLY
	EXPORT __Vectors
	
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	MOV R4, #8
	LDR R0, =NUM
	LDR R10, =DST
	LDR R1, [R0]
	
UP	AND R2, R1, #0x0F
	CMP R2, #0x0A
	ADDCS R2, #07
	ADD R2, #0x30
	STR R2, [R10], #1
	LSR R1, #4
	SUBS R4, #1
	BNE UP
	
STOP
	B STOP

NUM DCD 0xABCD4321
	AREA mydata, DATA, READWRITE
DST DCD 0
	END

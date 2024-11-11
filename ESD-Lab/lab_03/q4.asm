	AREA RESET, DATA, READONLY
	EXPORT __Vectors
	
__Vectors
	DCD 0x10001000 ; stack pointer value
	DCD Reset_Handler ; reset vectors
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler
	LDR R0, =SRC
	LDR R1, =DST
	MOV R2, #8
	LDR R3, [R0]
	
UP	AND R4, R3, #0x0F
	LSR R3, R3, #4
	STR R4, [R1], #4
	SUBS R2, R2, #1
	BNE UP

STOP
	B STOP

SRC DCD 0x12345678
	AREA mydata, DATA, READWRITE
DST DCD 0
	END

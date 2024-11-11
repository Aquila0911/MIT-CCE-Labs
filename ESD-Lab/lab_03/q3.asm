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
	LDR R0, =N
	LDR R3, =DST
	MLA R1, R0, R0, R0
	LSR R1, R1, #1
	STR R1, [R3]
	
STOP
	B STOP

N EQU 0x00000008
	AREA mydata, DATA, READWRITE
DST DCD 0
	END

	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000; Stack pointer value for empty stack
	DCD Reset_Handler; reset vectors
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler
	LDR R0, =SRC
	LDR R1, [R0]
	LDR R2, [R0, #4]
STOP
	B STOP
NUM EQU 10
SRC DCD 8, 0x12345678, 0xABCDEF1A
	END
;little endian is followed in ARM Processors
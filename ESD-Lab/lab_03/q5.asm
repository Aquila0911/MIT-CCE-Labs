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
	MOV R3, #0; to store packed val
	MOV R2, #8; loop
	MOV R4, #28; to send byte 1 to first posi
	
UP	LDR R5, [R0], #4
	LSL R5, R5, R4
	ORR R3, R3, R5
	SUB R4, R4, #4
	SUBS R2, #1
	BNE UP
	
	STR R3, [R1]
	
STOP
	B STOP

SRC DCD 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
	AREA mydata, DATA, READWRITE
DST DCD 0
	END

	AREA RESET, DATA,READONLY
	EXPORT __Vectors
	
__Vectors
	DCD 0x10001000 ; stack pointer value
	DCD Reset_Handler ; reset vectors
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler 
	LDR R7, =DST
	LDR R0, =SRC1
	LDR R1, =SRC2
	MOV R2, #4 ; r2 stores value for loop counter
	
UP	LDR R3, [R0], #4
	LDR R4, [R1], #4
	ADCS R5, R4, R3
	STR  R5, [R7], #4
	SUB R2, #1
	TEQ R2, #00
	BNE UP
	
STOP
	B STOP

SRC1 DCD 0x11111111, 0x33333333, 0x55555555, 0x77777777
SRC2 DCD 0x22222222, 0x44444444, 0x66666666, 0x88888888
	AREA mydata, DATA, READWRITE
DST DCD 0
	END

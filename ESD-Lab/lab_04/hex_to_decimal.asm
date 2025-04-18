	AREA RESET, DATA, READONLY
	EXPORT __Vectors
	
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler
	MOV R1, #0x0A
	MOV R10, #0
	LDR R4, =SRC
	LDR R0, [R4]
	LDR R7, =DST

UP	BL div
	LSL R2, R10
	ORR R9, R2
	ADD R10, #4
	CMP R3, #00
	MOV R0, R3
	MOV R3, #0
	BNE UP
	
	ORR R9, R3
	STR R9, [R7]
	B STOP
	
div	CMP R0, R1
	SUBCS R0, R1
	ADDCS R3, #1
	BCS div
	MOV R2, R0
	BX LR
	
STOP
	B STOP

SRC DCD 0x0000DEAD
	AREA mydata, DATA, READWRITE
DST DCD 0
	END

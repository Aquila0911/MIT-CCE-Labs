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
	LDR R0, =SRC1
	LDR R1, =SRC2
	LDR R2, [R0]
	LDR R3, [R1]
	LDR R4, =DST
	
UP  CMP R2, R3
	BEQ FIN
	SUBGT R2, R3
	SUBLE R3, R2
	B UP
	
FIN 
	STR R2, [R4]
	
STOP
	B STOP

SRC1 DCD 0x06
SRC2 DCD 0x08
	AREA mydata, DATA, READWRITE
DST DCD 0
	END

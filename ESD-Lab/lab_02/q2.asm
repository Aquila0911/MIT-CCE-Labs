	AREA RESET,DATA,READONLY
	EXPORT __Vectors
	
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	LDR R0, =SRC
	LDR R1, =DST
	
	MOV R8, #10

UP1	LDR R2, [R0], #4
	STR R2, [R1], #4
	SUBS R8, #1
	BNE UP1
	
	MOV R0, #0x10000000
	MOV R8, #9

	LDR R4, [R0]
UP2	LDR R5, [R0, #4]!
	ADDS R4, R5
	SUBS R8, #1
	BNE UP2
	
	STR R4, [R0, #4]
	
STOP
	B STOP

SRC DCD 0xAB12FE49, 0x12345678, 0xABCDEF12, 0x11111111, 0x22222222, 0x33334444, 0x44445555, 0x66778899, 0xAAAABBBB, 0xEFEFEFEF
	AREA mydata, DATA, READWRITE
DST DCD 0
	END
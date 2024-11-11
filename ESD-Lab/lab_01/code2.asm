	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000; Stack pointer value when stack is emtpy
	DCD Reset_Handler; reset vectors
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler
	MOV R0, #10
	MOV R1, #0x100000
	LDR R2, =0x100000
	MOV R3, #-3
	MOV R4, #2_1010
	MOV R5, #3_1010
STOP
	B STOP
NUM EQU 10
SRC DCD 0x00000008,0x12345600,0x34567891
	END

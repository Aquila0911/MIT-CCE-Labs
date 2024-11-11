	AREA RESET, DATA, READONLY
    EXPORT __Vectors
	
__Vectors
    DCD 0x10001000          ; Initial Stack Pointer
    DCD Reset_Handler       ; Reset Handler
    ALIGN
	AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

Reset_Handler
	LDR R1,=NUM
	LDR R13,=0x10001000
	MOV R2,#1
	BL fact1
	LDR R9,=DST
	STR R2, [R9]

STOP
	B STOP
	
fact1
	CMP R1,#1
	BEQ exit
	PUSH{R1}
	PUSH{LR}
	SUB R1,#1
	BL fact1
	
	POP{LR}
	POP{R1}
	MUL R2, R1, R2
	BX LR
	
exit
	MOV R2,#1
	BX LR

NUM DCD 5
	AREA mydata, DATA, READWRITE
DST DCD 0
	END

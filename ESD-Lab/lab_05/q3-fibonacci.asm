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
	LDR R6,=DST
	LDR R0,=NUM 
	LDR R0,[R0]
	MOV R2,#1
	MOV R1,#1
	PUSH{R1}
	PUSH{R2}
	BL FEB
	
DONE 
	STR R3,[R6]
	
STOP
	B STOP

FEB 
	POP{R2}
	POP{R1}
	ADD R3,R1,R2
	PUSH{R3,R1}
	SUBS R0,#1
	BEQ DONE
	BL FEB

NUM DCD 5
	AREA mydata, DATA, READWRITE
DST DCD 0
	END

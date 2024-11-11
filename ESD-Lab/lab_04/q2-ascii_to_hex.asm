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
	MOV R4, #4
	LDR R0, =NUM
	LDR R10, =DST
	LDR R1, [R0]; load first 8 digits
	
; process first 8 digits
UP	AND R2, R1, #0xFF
	CMP R2, #0x40; check if char is a letter
	SUBHI R2, #07; if letter, subtract 7. just do it.
	SUB R2, #0x30
	ADD R5, R2
	ROR R5, #28
	LSR R1, #8
	SUBS R4, #1
	BNE UP

; load next 8 digits for processing
	LDR R1, [R0, #4]
	MOV R4, #4
	
; process next 8 digits
UP2	AND R2, R1, #0xFF
	CMP R2, #0x40
	SUBHI R2, #07
	SUB R2, #0x30
	ADD R5, R2
	ROR R5, #28
	LSR R1, #8
	SUBS R4, #1
	BNE UP2
	
	ROR R5, #4
	STR R5, [R10]

STOP
	B STOP

NUM DCD 0x31433839, 0x45303236
	AREA mydata, DATA, READWRITE
DST DCD 0
	END

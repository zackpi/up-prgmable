; TEST_ENV:	basic lib of helper funcs
; author:	zackpi 
; version:	00


;-------------;
; ENVIRONMENT ;
;-------------;
stksize:	EQU 0FFh 

; init the prgm env safely
setup:	LXI SP, stack
	JMP main

; exit the prgm env safely
stop:	HLT


;--------;
; HELPER ;
;--------;

; 8 BIT ADD:  ans0 <- arg0 + arg1 
add_8b:	PUSH PSW	; subroutine entry procedure
	PUSH B
	LXI H, arg
	MOV A,M
	INR L
	MOV B,M

	ADD B
	STA ans

	POP B		; exit procedure
	POP PSW
	RET


;------;
; USER ;
;------;

; user entry point
main:	LXI H, arg	; caller entry procedure	
	MVI M, 2Ah	; arg0 	<- 2Ah
	INR L
	MVI M, 57h	; arg1 	<- 57h
	CALL add_8b	; ans0 	<- add_8b(2Ah,57h)
	
	JMP stop


;---------;
; STORAGE ;
;---------;

arg:	DS 8h
ans: 	DS 8h
	DS stksize	
stack: NOP
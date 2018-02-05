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

; 8 BIT SIGNED ADD:  A <- arg0 + arg1 
; modifies: PSW,B,HL
add_8b:	LXI H, arg	; enter subroutine procedure: read from arg storage
	MOV A,M
	INR L
	MOV B,M
	ADD B
	RET


;------;
; USER ;
;------;

; user entry point	
main:	LXI H, arg	; calling subroutine procedure: write to arg storage
	MVI M, 2Ah	; arg0 	<- 2Ah
	INR L
	MVI M, 57h	; arg1 	<- 57h
	CALL add_8b	;A 	<- add_8b(2Ah,57h)
	
	STA ans		; store answer and halt 
	JMP stop


;---------;
; STORAGE ;
;---------;

arg:	DS 8h
ans: 	DS 8h
	DS stksize	
stack: NOP
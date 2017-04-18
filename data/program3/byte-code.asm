DEC _i
DEC _num
DEC _temp
MOV _num, 0


loop:
	MOV _temp, _i
	MOD _temp, 5
	CMP _temp, 0
	JE found
	JNE notFound

found:
	ADD _num, 1
	ADD _i, 1
	JMP checkContinue
	
notFound:
	ADD _i, 1
	JMP checkContinue

checkContinue:
	CMP _i, 100
	JG endLoop
	JLE loop

endLoop:
	OUT _num










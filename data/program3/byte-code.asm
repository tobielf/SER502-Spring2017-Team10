DEC i
DEC num
DEC temp
MOV num, 0


loop:
	MOV temp, i
	MOD temp, 5
	CMP temp, 0
	JE found
	JNE notFound

found:
	ADD num, 1
	ADD i, 1
	JMP checkContinue
	
notFound:
	ADD i, 1
	JMP checkContinue

checkContinue:
	CMP i, 100
	JG endLoop
	JLE loop

endLoop:
	OUT num










DEC i
DEC sum
DEC temp
i is 1

loop:
	MOV temp, i
	MOD temp, 2
	CMP temp, 0
	JE even
	JNE nextStep

even:
	MOV temp, i
	MOD temp, 3
	CMP temp, 0
	JE factor3
	JNE nextStep


factor3:
	ADD sum, i
	JMP nextStep	

nextStep:
	ADD i, 1
	CMP i, 100
	JG endLoop
	JLE loop

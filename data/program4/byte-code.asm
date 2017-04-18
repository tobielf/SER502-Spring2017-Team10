DEC _i
DEC _sum
DEC _temp
MOV _i, 1

loop:
	MOV _temp, _i
	MOD _temp, 2
	CMP _temp, 0
	JE even
	JNE nextStep

even:
	MOV _temp, _i
	MOD _temp, 3
	CMP _temp, 0
	JE factor3
	JNE nextStep


factor3:
	ADD _sum, _i
	JMP nextStep	

nextStep:
	ADD _i, 1
	CMP _i, 100
	JG endLoop
	JLE loop

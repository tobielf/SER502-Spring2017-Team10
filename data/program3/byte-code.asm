DEC _i
DEC _num
MOV _num 0

MOV _i 1
loop1:
	CMP _i 100
	JE loop1_end
		if1:
			DEC _temp1
			MOV _temp1 _i
			MOD _temp1 5
			CMP _temp1 0
			JNE	if1_end
			ADD num 1
		
		if1_end:

		ADD _i 1
		JMP loop1

loop1_end:
	OUT _num












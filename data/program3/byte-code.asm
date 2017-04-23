DEC i
DEC num
MOV num 0

MOV i 1
loop1:
	CMP i 100
	JE loop1_end
		if1:
			DEC _temp1
			MOV _temp1 i
			MOD _temp1 5
			CMP _temp1 0
			JNE	if1_end
			ADD num 1
		
		if1_end:

		ADD i 1
		JMP loop1

loop1_end:
	OUT num












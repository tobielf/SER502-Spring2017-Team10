DEC i
DEC sum

MOV i 1
loop1：
	CMP i 100
	JE loop1_end
	if1:
		DEC _temp1 
		MOV _temp1 i
		MOD _temp1 2
		CMP _temp1 0
		JNE if1_end
			DEC _temp2
			MOV _temp2 i
			CMP _temp2 0
			JNE if2_end
				ADD sum i
		if2_end:
	if1_end:

loop1_end:
	OUT sum

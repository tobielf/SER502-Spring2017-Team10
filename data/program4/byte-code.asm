DEC _i
DEC _sum

MOV _i 1
loop1：
	CMP _i 100
	JE loop1_end
	if1:
		DEC _temp1 
		MOV _temp1 _i
		MOD _temp1 2
		CMP _temp1 0
		JNE if1_end
			DEC _temp2
			MOV _temp2 _i
			CMP _temp2 0
			JNE if2_end
				ADD _sum _i
		if2_end:
	if1_end:

loop1_end:
	OUT _sum

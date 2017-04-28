DEC i
DEC sum

MOV i 1
for1:
	CMP i 100
	JE for1_end
	if1:
		DEC _temp1 
		MOV _temp1 i
		MOD _temp1 2
		CMP _temp1 0
		JNE if1_end
		if2:
			DEC _temp2
			MOV _temp2 i
			MOD _temp2 3
			CMP _temp2 0
			JNE if2_end
				ADD sum i
		if2_end:
	if1_end:
    ADD i 1
    JMP for1
for1_end:
	OUT sum

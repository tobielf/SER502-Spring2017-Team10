DEC i
DEC j
DEC sum
DEC flag
MOV sum 0
MOV i 2
for1:
CMP i 100
JE for1_end
    MOV flag 0
    
    MOV j 2
    for2:
    CMP j i
    JE for2_end
        if1:
            DEC _temp1
            MOV _temp1 i
            MOD _temp1 j
        CMP _temp1 0
        JNE if1_end
            MOV flag 1
        if1_end:
    ADD j 1
    JMP for2
    for2_end:
    if2:
    CMP flag 0
    JNE if2_end
        DEC _temp2
        MOV _temp2 sum
        ADD _temp2 i
        MOV sum _temp2
    if2_end:

ADD i 1
JMP for1
for1_end:

OUT sum
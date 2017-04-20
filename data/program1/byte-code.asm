DEC x
DEC i
MOV i 1

DEC even
DEC odd
MOV x i
for1:
CMP x 26
JE for1_end
    if1:
        DEC _temp1
        MOV _temp1 x
        MOD _temp1 2
    CMP _temp1 0
    JNE else1
        DEC _temp2
        MOV _temp2 even
        ADD _temp2 1
        MOV even _temp 2
        JMP if1_end
    else1:
        DEC _temp3
        MOV _temp3 odd
        ADD _temp3 1
        MOV odd _temp3
    if1_end:
        ADD x 1
        JMP for1
for1_end:
    OUT even
    OUT odd

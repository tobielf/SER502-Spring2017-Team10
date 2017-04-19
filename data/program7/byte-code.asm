DEC a
DEC b
DEC i

MOV a 0
MOV b 1

MOV i 1
loop1:
CMP i 7
JE loop1_end
    DEC temp
    OUT b
    MOV temp b
    DEC _temp1
    MOV _temp1 a
    ADD _temp1 b
    MOV b _temp1
    MOV a temp
ADD i 1
JMP loop1
loop1_end:

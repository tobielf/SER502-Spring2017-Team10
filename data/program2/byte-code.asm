DEC x
DEC i
MOV i, 0

loop1:
CMP x, 100
JE loop1_end
    DEC _temp
    MOV _temp, x
    MOD _temp, 10
  CMP _temp, 0
  JNE endif
    DEC y
    MOV y, 0
    loop2:
    DEC _temp2
    MOV _temp2, x
    DIV _temp2, 10
    CMP y, _temp2
    JE loop2_end
        OUT 1
        ADD y, 1
        JMP loop2
    loop2_end:
    endif:
        OUT 0
    ADD x, 1
    JMP loop1
loop1_end





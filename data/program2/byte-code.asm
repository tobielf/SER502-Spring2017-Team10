DEC x
DEC i
MOV i 0

loop1:
CMP x 101
JE loop1_end
    if1:
        DEC _temp1
        MOV _temp1 x
        MOD _temp1 10
      CMP _temp 0
      JNE else1
        DEC y
        MOV y 0
        loop2:
            DEC _temp2
            MOV _temp2 x
            DIV _temp2 10
          CMP y _temp2
          JE loop2_end
            OUT 1
            ADD y 1
            JMP loop2
        loop2_end:
            JMP if1_end
    else1:  
        OUT 0
    if1_end:
        ADD x 1
        JMP loop1
loop1_end





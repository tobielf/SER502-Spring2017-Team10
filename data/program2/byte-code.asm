DEC x
DEC i
MOV i 0

for1:
CMP x 101
JE for1_end
    if1:
        DEC _temp1
        MOV _temp1 x
        MOD _temp1 10
      CMP _temp1 0
      JNE else1
        DEC y
        MOV y 0
        for2:
            DEC _temp2
            MOV _temp2 x
            DIV _temp2 10
          CMP y _temp2
          JE for2_end
            OUT 1
            ADD y 1
            JMP for2
        for2_end:
            JMP if1_end
    else1:  
        OUT 0
    if1_end:
        ADD x 1
        JMP for1
for1_end:





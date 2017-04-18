DEC x
DEC i
MOV i, 1

DEC even
DEC odd

loop:
CMP x, 25
JE loop_end
    DEC _temp
    MOV _temp, x
    MOD _temp, 2
  CMP _temp, 0
  JNE endif
        DEC _temp2
        MOV _temp2, even
        ADD _temp2, 1
        MOV even, _temp 2
  endif:
        DEC _temp3
        MOV _temp3, odd
        ADD _temp3, 1
        MOV odd, _temp3
ADD x, 1
JMP loop
loop_end:
OUT even
OUT odd

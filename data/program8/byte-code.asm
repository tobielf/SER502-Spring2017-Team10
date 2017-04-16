DEC i
DEC j
DEC sum
DEC flag

MOV i, 2
loop1:
CMP i, 100
JE loop1_end
    MOV flag, 0
    
    MOV j, 2
    loop2:
        DEC _temp1
        MOV _temp1, i
        DIV _temp1, 2
    CMP j, _temp1
    JE loop2_end
            DEC _temp2
            MOV _temp2, i
            MOD _temp2, j
        CMP _temp2, 0
        JNE endif1
            MOV flag, 1
        endif1:
    ADD j, 1
    JMP loop2
    loop2_end:

    CMP flag, 0
    JNE endif2
        DEC _temp3
        MOV _temp3, sum
        ADD _temp3, i
        MOV sum, _temp3
    endif2:

ADD i 1
JMP loop1
loop1_end:

OUT sum
DEC count
DEC i
DEC j

  MOV i 0
    for1:
    CMP i 5
    JGE for1_end
    MOV count 0

      MOV j i
        for2:
        CMP j 5
        JGE for2_end
          DEC _temp1
          MOV _temp1 count
          ADD _temp1 1
          MOV count _temp1

        DEC _temp2 
        MOV _temp2 j
        ADD _temp2 1
        MOV j _temp2
        JMP for2
        for2_end:

    OUT count
    DEC _temp3 
    MOV _temp3 i
    ADD _temp3 1
    MOV i _temp3
    JMP for1
    for1_end:

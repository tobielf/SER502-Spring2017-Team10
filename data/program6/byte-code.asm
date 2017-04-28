DEC count
DEC i
DEC j

  MOV i 0
    for1:
    CMP i 5
    JE for1_end
    MOV count 0

      MOV j i
        for2:
        CMP j 5
        JE for2_end
          DEC _temp1
          MOV _temp1 count
          ADD _temp1 1
          MOV count _temp1

        ADD j 1
        JMP for2
        for2_end:

    OUT count
    ADD i 1
    JMP for1
    for1_end:

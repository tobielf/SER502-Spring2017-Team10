DEC sum
DEC i
MOV sum 0

  MOV i 0
    loop1:
    CMP i 10
    JE loop1_end

      if1:
      DEC _temp1
      MOV _temp1 i
      MOD _temp1 3
      CMP _temp1 0
      JE endif1

        ADD sum i

      endif1:
    ADD i 1
    JMP loop1
    loop1_end:
OUT sum

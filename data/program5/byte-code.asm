DEC count
DEC sum
MOV count 1
MOV sum 0

  DEC i
  MOV i count
    loop1:
    CMP i 10
    JE loop1_end

      DEC temp1
      MOV temp1 i
      MOD temp1 3
      CMP temp1 0
      JE endif1

        ADD sum i

      endif1:
    ADD i 1
    loop1_end:
OUT sum

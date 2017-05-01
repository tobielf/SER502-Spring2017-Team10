DEC a 
DEC b 
DEC i 
MOV a 0
MOV b 1
MOV i 1
for1:  
CMP i 7
JGE for1_end 
stmt_list:  
DEC temp 
OUT b 
MOV temp b
DEC _temp1 
MOV _temp1 a
ADD _temp1 b
MOV b _temp1
MOV a temp
stmt_list_end:  
DEC _temp2 
MOV _temp2 i
ADD _temp2 1
MOV i _temp2
JMP for1 
for1_end:  

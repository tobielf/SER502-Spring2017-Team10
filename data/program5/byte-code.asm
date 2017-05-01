DEC sum 
DEC i 
MOV sum 0
MOV i 0
for1:  
CMP i 10
JGE for1_end 
if1:  
DEC _temp1 
MOV _temp1 i
MOD _temp1 3
CMP _temp1 0
JE if1_end 
DEC _temp2 
MOV _temp2 sum
ADD _temp2 i
MOV sum _temp2
if1_end:  
DEC _temp3 
MOV _temp3 i
ADD _temp3 1
MOV i _temp3
JMP for1 
for1_end:  
OUT sum 

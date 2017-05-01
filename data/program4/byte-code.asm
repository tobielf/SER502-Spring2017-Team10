DEC i 
DEC sum 
MOV i 1
for1:  
CMP i 100
JGE for1_end 
stmt_list:  
if1:  
DEC _temp1 
MOV _temp1 i
MOD _temp1 2
CMP _temp1 0
JNE if1_end 
if2:  
DEC _temp2 
MOV _temp2 i
MOD _temp2 3
CMP _temp2 0
JNE if2_end 
DEC _temp3 
MOV _temp3 i
ADD _temp3 sum
MOV sum _temp3
if2_end:  
if1_end:  
stmt_list_end:  
DEC _temp4 
MOV _temp4 i
ADD _temp4 1
MOV i _temp4
JMP for1 
for1_end:  
OUT sum 

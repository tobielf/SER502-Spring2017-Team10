DEC i 
DEC j 
DEC sum 
DEC flag 
MOV sum 0
MOV i 2
for1:  
CMP i 100
JGE for1_end 
stmt_list:  
MOV flag 0
MOV j 2
for2:  
CMP j i
JGE for2_end 
stmt_list:  
if1:  
DEC _temp1 
MOV _temp1 i
MOD _temp1 j
CMP _temp1 0
JNE if1_end 
MOV flag 1
if1_end:  
stmt_list_end:  
DEC _temp2 
MOV _temp2 j
ADD _temp2 1
MOV j _temp2
JMP for2 
for2_end:  
if2:  
CMP flag 0
JNE if2_end 
DEC _temp3 
MOV _temp3 sum
ADD _temp3 i
MOV sum _temp3
if2_end:  
stmt_list_end:  
DEC _temp4 
MOV _temp4 i
ADD _temp4 1
MOV i _temp4
JMP for1 
for1_end:  
OUT sum 

DEC i 
DEC num 
MOV num 0
MOV i 1
for1:  
CMP i 100
JGE for1_end 
stmt_list:  
if1:  
DEC _temp1 
MOV _temp1 i
MOD _temp1 5
CMP _temp1 0
JNE if1_end 
DEC _temp2 
MOV _temp2 num
ADD _temp2 1
MOV num _temp2
if1_end:  
stmt_list_end:  
DEC _temp3 
MOV _temp3 i
ADD _temp3 1
MOV i _temp3
JMP for1 
for1_end:  
OUT num 

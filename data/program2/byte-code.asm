DEC x 
DEC i 
MOV i 0
MOV x i
for1:  
CMP x 101
JGE for1_end 
if1:  
DEC _temp1 
MOV _temp1 x
MOD _temp1 10
CMP _temp1 0
JNE else1 
DEC y 
MOV y 0
DEC _temp2 
MOV _temp2 x
DIV _temp2 10
for2:  
CMP y _temp2
JGE for2_end 
OUT 1 
DEC _temp3 
MOV _temp3 y
ADD _temp3 1
MOV y _temp3
JMP for2 
for2_end:  
JMP if1_end 
else1:  
OUT 0 
if1_end:  
DEC _temp4 
MOV _temp4 x
ADD _temp4 1
MOV x _temp4
JMP for1 
for1_end:  

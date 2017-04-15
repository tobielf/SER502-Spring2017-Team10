# SER502-Spring2017-Team10
**Members**

@tobielf, Guo Xiangyu

@run-dong-zhu, Zhu Rundong

@XimingFeng, Feng Ximing

@kkmacart, MacArthur Katie

**Development Plan**

MacArthur Katie, Lexical Analysis(Tokenizing)

Feng Ximing, Syntax Analysis(Parsing)

Zhu Rundong, Semantic Analysis(Intermediate Code Generating)

Guo Xiangyu, Runtime Environment(Executing)

## System Requirement

**Platform**

    Linux
    MacOS

## Tools

[GNU Make](https://www.gnu.org/software/make/) is a tool which controls the generation of executables and other non-source files of a program from the program's source files.

[Doxygen](http://www.stack.nl/~dimitri/doxygen/) is the de facto standard tool for generating documentation from annotated C++ sources, but it also supports other popular programming languages such as C, Objective-C, C#, PHP, Java, Python, IDL (Corba, Microsoft, and UNO/OpenOffice flavors), Fortran, VHDL, Tcl, and to some extent D.

[Valgrind](http://valgrind.org) is an instrumentation framework for building dynamic analysis tools. There are Valgrind tools that can automatically detect many memory management and threading bugs, and profile your programs in detail. You can also use Valgrind to build new tools.


## Install Directions
## Build and Run Directions
## YouTube Video Link

## Language Name

**TEN** will be our language name, since we are team **TEN**. 

Also, in Chinese "ten" means perfect, we will try to make this small language project as perfect as possible in the limited time.


## Grammar Rule
```
grammar ten;
program : stmt_list ;
stmt_list : stmt ';' stmt_list | stmt ';' ;
stmt : decl_stmt | assign_stmt | if_stmt | for_stmt | print_stmt | ;
decl_stmt : 'var' ID ;
assign_stmt : ID 'is' expr ;
if_stmt : 'if' '(' boolean_expr ')' 'then' '{' stmt_list '}' | 
          'if' '(' boolean_expr ')' 'then' '{' stmt_list '}' 'else' '{' stmt_list '}' ;
for_stmt : 'for' ID 'from' expr 'to' expr 'step' expr '{' stmt_list '}' ;
print_stmt : 'print' expr ;
boolean_expr : expr '=' expr | expr '<>' expr |
               expr '<' expr | expr '<=' expr | 
               expr '>' expr | expr '>=' expr | 
               boolean_val ;
boolean_val : 'true' | 'false' ;
expr : term res1;
res1 : '+' term | '-' term | ;
term : factor res2;
res2 : '*' factor | '/' factor | '%' factor |  ;
factor : '(' expr ')' | NUMBER | ID ;
NUMBER : [0-9]+ ;
ID : [a-z|A-Z]+ ;
WS : [ \t\r\n]+ -> skip ;
```

## Byte Code
```
Type 1: declare
DEC var1						; declare a variable

Type 2: assignment
MOV var1, var2/value		; assign var2/value to var1

Type 3: arithmetic operation
ADD var1, var2/value		; add var2/value to var1
SUB var1, var2/value		; sub var2/value from var1
MUL var1, var2/value		; mul var2/value to var1
DIV var1, var2/value		; div var2/value from var1
MOD var1, var2/value		; mod var1 with var2/value

Type 4: compare and jump operation
CMP var1, var2/value		; CMP var1 and var2/value, set $flag = var1 - var2/value.
JE  label			; Jump to label if $flag Equal to zero.
JNE label			; Jump to label if $flag Not Equal to zero.
JL  label			; Jump to label if $flag Less than zero.
JLE label			; Jump to label if $flag Less than or Equal to zero.
JG  label			; Jump to label if $flag Great than zero.
JGE label			; Jump to label if $flag Great than or Equal to zero.
JMP label			; Jump to label, always.

Type 5: output result
OUT var1/value			; Output var1/value.
```

## Design Details
* Paradigm of the Language
	
		imperative paradigm

* Parsing Process(Technique)

	![Parsing Process](./Parsing Process.png)
		
		TopDown Parser
		Syntax Directed Translation
		Operational Semantic

* Example Program in High Level Language

	For more example, please see [here](https://github.com/tobielf/SER502-Spring2017-Team10/tree/master/data)

	Example: counting the sum of all the even and odd numbers between 1 and 100 using our language.
	
	```
	var i;
	var evenSum;
	var oddSum;
	evenSum is 0;
	oddSum is 0;
	for i from 1 to 100 step 1 {
	    if ((i % 2) = 0) then {
	        evenSum is evenSum + i;
	    } else {
	        oddSum is oddSum + i;
	    };
	};
	print evenSum;
	print oddSum;
	```
* Design Decision
	1. No dynamic memory allocation and function call in our language to keep it as simple as possible.
	2. Only support one primitive type(integer), so we don't need to do the type checking in our compiler.
	3. Ambiguous in "Dangling else". This ambiguity is resolved by forcing the user to use `{` and `}` to incorporating a statement list.
	4. For virtual machine(runtime environment), we didn't limited the number of registers. So the intermediate code can use DEC var to declare as many variables as it need.
	5. Also in the virtual machine, it provided an OUT instruction to allow user to print the value inside the store.
* Data Structure

		ArrayList for symbol table.
		Left-child right-sibling binary tree for syntax tree.
* Recursion method in the grammar

		Right Recursion
* Tools & developing language planning to use

		C programming as the developing language
		ANTLR helping verify the grammar rule
		Valgrind checking memory leaks in the code
* Runtime Environement

	It will be a virtual machine, changing the storage state by executing the byte-code command in sequence.

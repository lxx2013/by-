assume cs:code,ds:data ,ss:stack
data segment
BUF			db ffh dup(?)					; 存读到的数字
COUNT		dw ffh dup(?)
ERR 		db 257	
ERR 		dw "ABc"
ERR 		dd "Ac"		
data ends

code segment
printf  MACRO x
abcd:	
		int 21H
		int 22H
test:
		int 21h
		ENDM

start:
	;初始化
	int 21h
second:
	

code ends
end start

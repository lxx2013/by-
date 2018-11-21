assume cs:code,ds:data
data segment
BUF			db ffh dup(?)					; 存读到的数字
ERR 		db 257	
NUM 		dw "abcd"
data ends

code segment

start:
	sub bx,[ax] 			
	mul [bx+1] 	
	mov [bx],[bx+1]
	loop start_false 			
	mov ax,4c00h
	int 21h 				; 调用中断驱动，结束程序
	
second:						; 定义函数
	mov ah,02h
	mov dl,'ABC'
	int 21h
	ret

code ends
end start

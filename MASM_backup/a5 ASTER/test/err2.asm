assume cs:code,ds:data,ss:stack
data segment
BUF			db 0ffh dup(?)					; 存读到的数字
ERR 		db 256	
NUM 		db "abcd"
data ends

code segment

start:
	loop start_false 
	jmp second				;这句是对的，可以往后跳

loop1:
	mov cx,2
	loop loop1
loop2:
	push 3
	pop ax
	cmp ax,3
	je loop2
loop3:
	add ax,30
	cmp ax,20
	jge loop3
loop4:
	mul ah
	div al
	cmp cx,10 				;循环内部未修改条件变量
	jle loop4

	mov ax,4c00h
	int 21h 				; 调用中断驱动，结束程序

	
second:						; 定义函数
	mov ah,02h
	mov dl,03
	int 21h
	mov ah,02h
	mov dl,'A'
	int 21h
	ret

code ends
end start

assume cs:code,ds:data
data segment
BUF			db 0ffh dup(?)					; 存读到的数字
ERR 		dw 256	
NUM 		db "abcd"
data ends

code segment
printf  MACRO x
test:
		mov x,12
		int 21h
		ENDM

start:
	mov ax,offset BUF 		; mov指令 ＋ 偏移量寻址
	add ax,ERR 				; add指令 ＋ 直接寻址
	sub bx,[bx] 			; sub指令 ＋ 寄存器寻址
	mul byte ptr [bx+1] 	; mul指令 ＋ 寄存器加偏移寻址
	div word ptr [bx+di+1] 	; div指令 ＋ 更灵活的寻址
	inc NUM					; inc指令 
	dec cx					; dec指令 
	loop start 				; loop指令 
	cmp cx,ax				; cmp指令 
	jge  start				; 比较指令
	call second 			; call指令
	push ax					; push指令
	pop  ax					; pop指令
	mov ax,4c00h
	int 21h 				; 调用中断驱动，结束程序
	
second:						; 定义函数
	mov ah,02h
	mov dl,'A'
	int 21h
	ret

code ends
end start

assume cs:code,ds:data,ss:stack
data segment
BUF			db 48 dup(0)					; 存读到的数字
NUM 		db 0
COUNT		dw 0							; 计数
MSG			db "Please input n : $"	
data ends

stack segment 
BUF	db 1024 dup(?)
stack ends

code segment
printf  MACRO x
		push ax
		push cx
		mov cx,x
		mov ah,2
		mov dl,cl
		add dl,30h
		int 21H
		pop cx
		pop ax
		ENDM
start:
	;初始化
	mov ax,data
	mov ds,ax
	mov ax,stack
	mov ss,ax
	mov sp,1024

	call multiply
	call print_num


	mov ax,4c00H
	int 21H
;****************
; 附1.高精度乘法函数
;**************** 	
multiply:	;函数定义，入口dh，输出数字*dh
	m_store:
			push ax
			push bx
			push cx
			push dx
			
			mov bx,offset BUF
			mov cx,COUNT

	multi:	mov al,[bx]
			mul dh
			mov [bx],al
			inc bx
			loop multi 				;将一串数字乘上bh的值


	ret


;****************
; 附2.输出函数
;****************
print_num:     ;函数定义，输出COUNT个数字。
	p_store:	
			push ax				; dx用来存放常数
			push bx				; ax用来存放数据
			push cx

			dec si
			call print_num
			int 21H
			
	ret
code ends
end start

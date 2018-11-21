assume cs:code,ds:data ,ss:stack
abc segment
MSG			db ffh dup(0)
.
MSG			db "Please input n : $"	
MSG			dd "Please input n : $"	
MSG			dw "Please input n : $"	
abc ends
data segment
BUF			db 48 dup(0)					; 存读到的数字
NUM 		db 0
COUNT		dw 0							; 计数
MSG			db "Please input n : $"	
data ends

stack segment stack
	db 1024 dup(?)
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
	
;****************
; 1.读控制台输入
;****************
	;input n
	; mov ax,n
	;begin
	mov dx,offset MSG
	mov ah,9
	int 21H
read:
	mov ah,01
	int 21H

	mov ch,13			; '\n'
	cmp al,ch
	je num_finish		; 一个数字已读完
	mov cl,al
	sub cl,48
	mov al,NUM
	mov dh,10
	mul dh
	add al,cl
	mov NUM,al
	jmp read

num_finish:
	mov cx,0
	mov bx,offset BUF
	mov al,1
	mov [bx],al
	mov COUNT,1
	mov dh,NUM
	mov cl,dh
	cmp dh,1
	je print_1		;如果输入的数字是1就直接输出
	cmp dh,0
	je print_1
	dec cx
;****************
; 2.执行阶乘
;**************** 
jiecheng:
	call multiply
	dec dh
	loop jiecheng
print_1:
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

			mov bx,offset BUF
			mov cx,COUNT
	m_adc:	mov al,[bx]
			mov ah,0
			cmp al,10
			jb  not_c
			mov dl,10
			div dl
			mov [bx],ah
			add [bx+1],al
			cmp cx,1
			jne not_c
			inc COUNT				;如果最后一位还进位了，就让计数器加一
			inc cx
	not_c:	inc bx
			loop m_adc				;执行进位操作

	m_restore:
			pop dx
			pop cx
			pop bx
			pop ax
	ret
;****************
; 附2.输出函数
;****************
print_num:     ;函数定义，输出COUNT个数字。
	p_store:	
			push ax				; dx用来存放常数
			push bx				; ax用来存放数据
			push cx
			push dx
			mov bx,offset BUF
			mov cx,COUNT
			mov si,cx
			mov ah,2
	p_print:	
			mov dl,[bx+si-1]			; 取一个数
			add dl,48
			int 21H
			dec si
			loop p_print

	huanhang:
			mov ah,2
			mov dl,10;'\n'
			int 21H

	p_restore:
			pop dx
			pop cx
			pop bx
			pop ax
	ret
code ends
end start

#各种Exp表达式，包含若干种错误处理
#从上到下从简单到复合，最后是错误处理
void main ()
{
	Output = 1 + 4;
	print();
	Output = Output - 3;
	print();
	Output = Output * 3;
	print();
	Output = Output / 3;
	print();
	Output = Output % 3;
	print();
	Output = 1+2*3-4%5;
	print();

	Output = +1;
	print();
	Output = -1;
	print();
	Output = +-2; 
	print();    
	Output = 1+-2;	
	print(); 
}

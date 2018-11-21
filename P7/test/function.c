#各种Function表达式，包含若干种错误处理

void fib()
{
	if(Output<1000)
	{
		Output = Output + Output;
		print();
		fib();
	}
}
void main ()
{
	Output =1;
	fib();
}

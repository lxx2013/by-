#各种while表达式，包含若干种错误处理
#从上到下从简单到复合，最后是错误处理
#其实这个文件我只是把if.c的if字符串替换为while
void main ()
{
	while(1<2)
	{
		while(1>2)
		{ }
	}
	while(1<=2)
	{}
	while(1>=2)
	{}
	while(1==2)
	{}
	while(1!=2)
	{}

	while(1-2<0)
		;


	while ( 1>2
		;


	while (  1+2*3-2 < (5)		#这里正确识别了,有些同学的文法可能不识别
		;

	while (  1+2*3-2 < (5		#首先缺少的是Exp的右括号，其次缺while的右括号
		;


}

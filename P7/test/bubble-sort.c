#include<stdio.h>
void main()
{
    const int num = 6;
    int a[10];
    int i=0,j,t;
    while(i<10)
    {
        scan();
        a[i] = Input;
        i=i+1;
    }
    i=0;
	while(i<10)
	{
		j=i+1;
		while(j<10)
		{
			if(a[i]>a[j])
			{	
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
			j=j+1;
		}
		i=i+1;
	}
    i=0;
    while(i<10)
    {
        Output = a[i];
        print();
        i=i+1;
    }
    
}
		
			
	

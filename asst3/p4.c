#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h> 
#include<math.h>


int main(int argc,char *argv[])
{
	if(argc!=2) {printf("invalid input\n");exit(0);}
	int n=atoi(argv[1]);

	pid_t pid;
	pid=fork();

	if(pid==0)
	{
		printf("fibonacci series %d\n",n);
		int a=0,b=1,c=0;
		for(int i=0;i<n;i++)
		{printf("%d\n",a);
		c=a+b;
		a=b;
		b=c;
		}
	}
	else if(pid>0)
	{
		wait(NULL);
		printf("prime series\n");
		int count=0,i=2;
		while(count<n)
		{
		int flag=1;
		for(int j=2;j<i;++j)
		{if(i%j==0)
		flag=0;
		}
		if(flag==1)
		{
			printf("%d\n",i);
			count++;
		}
		i++;
		}
		
	}
	return 0;
}
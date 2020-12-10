#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h> 
#include<math.h>

int main(int argc,char *argv[])
{
	if(argc!=3) {printf("invalid input\n");exit(0);}
	int lnum=atoi(argv[1]),hnum=atoi(argv[2]);
	int sum[1000]={0};
	
	pid_t pid;
	pid=vfork();
	//printf("%d",pid);

	if(pid==0)
	{
		
		for(int i=lnum;i<hnum;++i)
		{
		int k,n=i;
		int count=0;
		while(n>0)
		{
			n/=10;
			count++;
		}
		n=i;
		while(n>0)
		{
			k=n%10;
			n=n/10;
			sum[i-lnum]+=pow(k,count);
		}
		}
		exit(0);
	}
	else if(pid>0)
	{
		wait(NULL);
		printf("child terminated\nList of armstrong numbers\n");
		for(int i=lnum;i<hnum;++i)
		if(sum[i-lnum]==i)
		printf("%d\n",i);
				
	}
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	if(argc!=2) {printf("invalid input\n");exit(0);}
	int n=atoi(argv[1]);
	
	pid_t pid;
	pid=fork();

	if(pid==0)
	{
		printf("even series\n");
		for(int i=0;i<=n;i=i+2)
		printf("%d\n",i);
		
	}
	else if(pid>0)
	{
		printf("odd series\n");
		for(int i=1;i<=n;i=i+2)
		printf("%d\n",i);
	}
	return 0;
}
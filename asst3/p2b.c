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
		int sume=0;
		printf("even series sum\n");
		for(int i=0;i<=n;i=i+2)
		sume+=i;
		printf("%d\n",sume);
		
	}
	else if(pid>0)
	{
		int sumo=0;
		printf("odd series sum\n");
		for(int i=1;i<=n;i=i+2)
		sumo+=i;
		printf("%d\n",sumo);
	}
	return 0;
}
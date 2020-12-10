#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main()
{
	printf("before fork\n");
	pid_t pid=fork();
	if(pid==0)
	{
		printf("child process\n");
		exit(0);
		
	}
	else
	{
		sleep(20);
		printf("parent process\n");
	}
}
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main()
{
	printf("before fork\n");
	pid_t pid=fork();
	
	if(pid>0)
	{
		printf("parent process\n");
		
	}
	else
	{
		sleep(20);
		printf("orphan child process\n");
	}
}
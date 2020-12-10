#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	pid_t pid[10];
	pid[2]=fork();//1 forks 2

	if (pid[2]>0)
	{	
		pid[3]=fork();//1 forks 3
		if(pid[3]==0)
		{	
			printf("1 forked 3\n");
			pid[7]=fork();//3 forks 7
			if(pid[7]==0)
			{
				printf("3 forked 7\n");
			}
		}
	}
	else if(pid[2]==0)
	{
		printf("1 forked 2\n");
		pid[4]=fork();//2 forks 4
		if(pid[4]>0)
		{
			pid[5]=fork();//2 forks 5
			if(pid[5]>0)
			{	pid[6]=fork();//2 forks 6

				if(pid[6]==0)
				{
					printf("2 forked 6\n");
				}
			}
			else if(pid[5]==0)
			{	
				printf("2 forked 5\n");
				pid[9]=fork();//5 forks 9
				if(pid[9]==0) printf("5 forked 9\n");
			}
		}
		else if(pid[4]==0)
		{
			printf("2 forked 4\n");
			pid[8]=fork();//4 forks 8
			if(pid[8]==0) printf("4 forked 8\n");
		}
	}
	return 0;
}


#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main()
{

	// create a shared memory integer variable
	// to count the total no of fork calls
	key_t key = IPC_PRIVATE;
	int shm_id;
	size_t shm_size=sizeof(int);
	if((shm_id=shmget(key,shm_size,IPC_CREAT | 0666))==-1)
	{
		perror("shmget");
		exit(1);
	}
	int *shm_count;
	if((shm_count=shmat(shm_id,NULL,0))==(int *)-1)
	{
		perror("shmat");
		exit(1);
	}
	*shm_count=1; // initally 1 fork is done

	pid_t pid=fork();

	if(pid==-1)
	{
		printf("fork failed!\n");
		exit(1);
	}
	else if (pid==0) // child block
	{
		while(1)
		{
			pid=fork(); // fork repeatedly until fork returns -1
			if(pid==-1)
				break;
			else if(pid==0) // increment count by 1 in each child
			{
				*shm_count=*shm_count+1;
				exit(0);
			}
		}
		exit(0);
	}
	else
	{
		wait(NULL); // wait for the child to finish all fork calls
		printf("total number of successful fork calls = %d\n",*shm_count);
	}
}
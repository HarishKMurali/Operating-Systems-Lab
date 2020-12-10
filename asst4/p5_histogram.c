#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
//#include<conio.h>
#include<sys/wait.h>
#include<string.h>
int* create_shm_array(int size)
{
	key_t key = IPC_PRIVATE;

	int shm_id;
	size_t shm_size=size*sizeof(int);
	if((shm_id=shmget(key,shm_size,IPC_CREAT | 0666))==-1)
	{
		perror("shmget");
		exit(1);
	}

	int *shm_arr;
	if((shm_arr=shmat(shm_id,NULL,0))==(int *)-1)
	{
		perror("shmat");
		exit(1);
	}

	return shm_arr;
}


int main()
{
	
	int *shm_arr=create_shm_array(95);
	for(int i=0;i<95;++i)
	{
		pid_t pid=fork();
		if(pid==0)
		{
			FILE *ptr=fopen("ip.txt","r");
			shm_arr[i]=0;
			char c;
			while((c=fgetc(ptr))!=EOF)
			{
				if(c==i+32)
				{
					shm_arr[i]++;
				}
			}
			fclose(ptr);
			exit(0);
		}
		if(pid>0)
		wait(NULL);
	}
	for(int i=0; i<95; ++i)
  {
    if(shm_arr[i]>0)
		{
		if(i!=94)
			putchar(i+32);
		else
			printf("others");
    printf(" | ");   
    for(int j=0; j < shm_arr[i]; ++j)
      putchar('*');

    putchar('\n');
		}
	}
	return 0;
}
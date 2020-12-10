#include <stdio.h> 
#include <stdlib.h> 
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
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
	int m=2,n=3,p=3,q=2;
	if(n!=p)
	printf("matrix mult cant be done");

	
	int *res[m];
	for(int i=0;i<m;++i)
	res[i]=create_shm_array(q);
	
	int a[][3]={{2,3,4},{5,6,1}};
	int b[][2]={{7,8},{9,0},{1,2}};

	int i, j, k; 
  pid_t pid=fork();
	if(pid==0)
	{
	for (i = 0; i < m; i++) 
  { 
    for (j = 0; j < q; j++) 
    { 
      res[i][j] = 0; 
      for (k = 0; k < p; k++) 
			{
				pid=fork();
				if(pid==0)
				{
        res[i][j] += a[i][k]*b[k][j]; 
				exit(0);
				}
			}
		} 
  }
	exit(0);
	}
	else if(pid>0)
	{
		wait(NULL);
		for(int ti=0;i<m;++i)
	{
		for(int j=0;j<q;++j)
		printf("%d ",res[i][j]);
		printf("\n");
	} 
	}
	return 0;
	
}
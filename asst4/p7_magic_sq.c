#include <stdio.h> 
#include <stdlib.h> 
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h>

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// A function to implement bubble sort 
void bubbleSort(int arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 

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
	int n;
	int mat[10][10];
	printf("enter n\n");
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	for(int j=0;j<n;++j)
	scanf("%d",&mat[i][j]);
	int sum=(n*(n*n+1))/2;
	int total_sum=sum*n;
	int *flag=create_shm_array(1);
	flag[0]=1;
	pid_t qid,rid,pid=vfork();//A
	if(pid==0)
	{	
		pid_t id=fork();//B
		if(id==0){	
		int sumd1=0;
		for(int i=0;i<n;++i)
		sumd1+=mat[i][i];

		if(sumd1!=sum)
		flag[0]=0;
		exit(0);
		}
		else
		{
		int sumd2=0;
		for(int i=0;i<n;++i)
		sumd2+=mat[i][n-1-i];

		if(sumd2!=sum)
		flag[0]=0;
		exit(0);
			
		}
		
	}
	else
	{
		qid=vfork();//C
		if(qid==0)
		{
			for (int i = 0; i < n; i++) { 
       pid_t id=fork();//D
			 if(id==0){   
        int rowSum = 0;      
        for (int j = 0; j < n; j++) 
            rowSum += mat[i][j]; 
          
        // check if every row sum is 
        // equal to prime diagonal sum 
        if (rowSum != sum) 
            flag[0]=0; 
						exit(0);
			 }
    }
		exit(0);
		}
		else
		{
			rid=vfork();//E
			if(rid==0)
			{
				pid_t fid=fork();//F
				if(fid==0){
				for (int i = 0; i < n; i++) { 
				pid_t id=fork();//G
			 	if(id==0){ 
          
        int colSum = 0;      
        for (int j = 0; j < n; j++) 
            colSum += mat[j][i]; 
  
        // check if every column sum is  
        // equal to prime diagonal sum 
        if (sum != colSum)  
        flag[0]=0; 
				exit(0);
				 }
				} 
				}
				else
				{
					int arr[100],k=0;
					for(int i=0;i<n;++i)
					for(int j=0;j<n;++j)
						arr[k++]=mat[i][j];
					bubbleSort(arr,n*n);
					for(int i=0;i<n*n-1;++i)
					if(arr[i]==arr[i+1])
					flag[0]=0;
					exit(0);
				
				}
				
			exit(0);
			}
			
		} 
		}
		int status;
		waitpid(pid,&status,0);
		waitpid(qid,&status,0);
		waitpid(rid,&status,0);
		if(flag[0]==1)
		printf("matrix is magic square\n");
		else
		printf("matrix is not magic square\n");
		return 0;

}

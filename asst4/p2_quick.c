#include<stdio.h>
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


void swap(int* a, int* b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    
    int i = (low - 1);   
  
    for (int j = low; j <= high- 1; j++) 
    { 
       if (arr[j] < pivot) 
        { i++;     
          swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i+1],&arr[high]); 
    return i+1; 
} 
  
void quicksort(int arr[], int low, int high,int k) 
{ 
    if (high>low) 
    { 
        int q = partition(arr, low, high);  
				pid_t qid,pid=fork();
				if(pid==0)
				{
        quicksort(arr, low, q-1,k); 
				exit(0);
				}
				else if(pid>0)
				{
					qid=fork();
					if(qid==0)
					{
        		quicksort(arr, q+1, high,k); 
						exit(0);
					}
				}
				int status;
				waitpid(pid,&status,0);
				waitpid(qid,&status,0);
    } 
} 

int main()
{
	int n;
    int k;

	printf("enter the value of n\n");
	scanf("%d",&n);

	int *a=create_shm_array(n);
	
	for(int i=0;i<n;++i)
		scanf("%d",&a[i]);

	//printf("\nenter k:\n");
	//scanf("%d",&k);
	k=n;
	quicksort(a,0,n-1,k);

	printf("\nSorted array:\n");

	for(int i=0;i<k;++i)
		printf("%d ",a[i]); 
		printf("\n");
	return 0;
}
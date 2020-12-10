#include <stdio.h> 
#include <stdlib.h> 
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
  
// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
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
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            arr[k] = L[i]; 
            i++; 
        } 
        else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l + (r - l) / 2; 
  
        // Sort first and second halves 
				pid_t qid,pid=fork();
				if(pid==0)
				{
        mergeSort(arr, l, m); 
				exit(0);
				}
				if(pid>0)
				{
				qid=fork();
				if(qid==0)
				{
        mergeSort(arr, m + 1, r); 
				exit(0);
				}
				}
				int status;
				waitpid(pid,&status,0);
				waitpid(qid,&status,0);
			
        merge(arr, l, m, r); 
    } 
} 
  
/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size) 
{ 
    int i; 
    for (i = 0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
} 
  
/* Driver program to test above functions */
int main() 
{ 
    int arr_size;
    printf("enter the value of n\n");
	scanf("%d",&arr_size);
    int a[20];
    int *arr = create_shm_array(arr_size);
    for(int i=0;i<arr_size;++i)
		scanf("%d",&a[i]);
    //int a[]={ 14, 11, 13, 15, 6, 7 }; 
    for(int i=0;i<6;++i)
    arr[i]=a[i];
    //int arr_size = sizeof(a) / sizeof(a[0]); 
  
    printf("Given array is \n"); 
    printArray(arr, arr_size); 
  
    mergeSort(arr, 0, arr_size - 1); 
  
    printf("\nSorted array is \n"); 
    printArray(arr, arr_size); 
    return 0; 
} 
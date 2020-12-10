#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *runner(void* param);
int num,arr[20];
struct passing
{
	int b,e;
};
int tcount=0;

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

		struct passing p,q;
		p.b=l;p.e=m;
		q.b=m+1;q.e=r;
		pthread_t tid[2];
		pthread_create(&tid[0],NULL,runner,&p);
		pthread_create(&tid[1],NULL,runner,&q);
		pthread_join(tid[0],NULL);
		pthread_join(tid[1],NULL);
 
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

int main(int argc,char *argv[])
{
	num=atoi(argv[1]);
	if(argc!=num+2) {printf("invalid input\n");exit(0);}
	
	for(int i=0;i<num;++i)
	{
		arr[i]=atoi(argv[i+2]);
	} 

	printf("Given array is \n"); 
    printArray(arr, num);

	mergeSort(arr, 0, num - 1); 
  
    printf("\nSorted array is \n"); 
    printArray(arr, num); 
    printf("number of threads used:%d\n",tcount);
	return 0; 
} 

void *runner(void* param)
{
	struct passing *p=(struct passing*)param;
    tcount++;
	mergeSort(arr,p->b,p->e);
}
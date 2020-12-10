#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *runner(void* param);
int num,arr[20],k,tcount=0;
struct passing
{
	int b,e,k;
};

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

				struct passing p,r;
				p.b=low;p.e=q-1;p.k=k;
				r.b=q+1;r.e=high;r.k=k;
				pthread_t tid[2];
				pthread_create(&tid[0],NULL,runner,&p);
				pthread_create(&tid[1],NULL,runner,&r);
				pthread_join(tid[0],NULL);
				pthread_join(tid[1],NULL);

    } 
} 

int main(int argc,char *argv[])
{
	num=atoi(argv[1]);
	if(argc!=num+2) {printf("invalid input\n");exit(0);}
	
	for(int i=0;i<num;++i)
	{
		arr[i]=atoi(argv[i+2]);
	} 

	k=num;
	quicksort(arr,0,num-1,k);

	printf("\nSorted array:\n");

	for(int i=0;i<k;++i)
		printf("%d ",arr[i]); 
		printf("\n");
	printf("Number of threads used:%d\n",tcount);
	return 0;
}

void *runner(void* param)
{
	struct passing* p=(struct passing*)param;
	//printf("%d ",++tcount);
	++tcount;
	quicksort(arr,p->b,p->e,p->k); 
}
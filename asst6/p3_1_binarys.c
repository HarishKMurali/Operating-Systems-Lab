#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h> 
#include<pthread.h>
#include<math.h>
#define MAX_THREAD 4
void *runner(void *param);
int arr[30],start=0,end,key,num;
int part=0;

void binary_search (int start, int end, int key,int part){
	int mid = (end + start)/2;
	
	if(start > end){
	return;
	}
	if(start == end){
	if(arr[mid] == key){
			printf("Key found at address: %d by thread %d\n", mid,part);
	}
	return;
	}

	if(start+1 == end){
	binary_search(start, start, key,part);
	binary_search(end, end, key,part);
	}
	if(arr[mid] == key){
	printf("Key found at address: %d by thread %d\n", mid,part);
	} 
	pid_t pid = fork();
	if(pid == 0){
	binary_search(start, mid-1, key,part);
	}
	else{
	binary_search(mid+1, end, key,part);
	}
}

int main(int argc,char *argv[])
{
	num=atoi(argv[1]);
	if(argc!=num+3) {printf("invalid input\n");exit(0);}
	
	for(int i=0;i<num;++i)
	{
		arr[i]=atoi(argv[i+2]);
	} 
	key=atoi(argv[num+2]);
	end=num-1;
	pthread_t threads[MAX_THREAD]; 

	if(num/MAX_THREAD<=1)
	{
		printf("more number of threads!");
		exit(0);
	}
  
  for (int i = 0; i < MAX_THREAD; i++) 
    pthread_create(&threads[i], NULL,runner, (void*)NULL); 
  
  for (int i = 0; i < MAX_THREAD; i++) 
    pthread_join(threads[i], NULL); 
	
	return 0;
}

void* runner(void* param) 
{ 
  
    // Each thread checks 1/4 of the array for the key 
    int thread_part = part++; 
    int mid; 
  
    int low = thread_part * (num / MAX_THREAD); 
    int high = (thread_part + 1) * (num / MAX_THREAD); 

		binary_search(low,high,key,part);
		pthread_exit(0);
}
		
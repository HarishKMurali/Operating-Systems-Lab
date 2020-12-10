#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h> 
#include<math.h>
void binary_search (int arr[], int start, int end, int key);
int main(int argc,char *argv[])
{
	int num=atoi(argv[1]);
	if(argc!=num+3) {printf("invalid input\n");exit(0);}
	
	int arr[20];
	for(int i=0;i<num;++i)
	{
		arr[i]=atoi(argv[i+2]);
	} 
	int x=atoi(argv[num+2]);
	binary_search(arr,0,num,x);
	return 0;
}

void binary_search (int arr[], int start, int end, int key){
	int mid = (end + start)/2;
	
	if(start > end){
	return;
	}
	if(start == end){
	if(arr[mid] == key){
			printf("Key found at address: %d\n", mid);
	}
	return;
	}

	if(start+1 == end){
	binary_search(arr, start, start, key);
	binary_search(arr, end, end, key);
	}
	if(arr[mid] == key){
	printf("Key found at address: %d\n", mid);
	} 
	pid_t pid = fork();
	if(pid == 0){
	binary_search(arr, start, mid-1, key);
	}
	else{
	binary_search(arr, mid+1, end, key);
	}
}
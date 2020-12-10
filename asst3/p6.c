#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h> 
#include<math.h>

int main(int argc,char *argv[])
{
	
	int num=atoi(argv[1]);
	if(argc!=num+2) {printf("invalid input\n");exit(0);}
	//int sum=0;
	
	int arr[20];
	for(int i=0;i<num;++i)
	{
		arr[i]=atoi(argv[i+2]);
	} 

	pid_t pid;
	pid=fork();

	if(pid<0){printf("fork failed\n");exit(0);}

	if(pid==0)
	{
		for (int i = 1; i < num/2; i++) 
  	{  
     int key = arr[i];  
     int j = i - 1;  
  
  	  while (j >= 0 && arr[j]>key) 
      {  
        arr[j + 1] = arr[j];  
        j = j - 1;  
      }  
      arr[j + 1] = key;  
 	 	}
		printf("first half ascending order by child\n");
		for(int i=0;i<num/2;++i)
		printf("%d ",arr[i]);
		printf("\n");
		
	}
	else if(pid>0)
	{
		wait(NULL);
		for (int i = num/2+1; i < num; i++) 
  	{  
     int key = arr[i];  
     int j = i - 1;  
  
  	  while (j >= num/2 && arr[j]<key) 
      {  
        arr[j + 1] = arr[j];  
        j = j - 1;  
      }  
      arr[j + 1] = key;  
 	 	}
		printf("second half descending order by parent\n");
		for(int i=num/2;i<num;++i)
		printf("%d ",arr[i]);
		printf("\n");
	}
	return 0;
}

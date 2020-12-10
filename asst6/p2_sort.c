#include <pthread.h> 
#include <stdio.h> 
#include<stdlib.h>
#include<string.h>
int sum; /* this data is shared by the thread(s) */ 
void *runner (void *param); /* the thread */
int num;
int arr[2][30];
int main(int argc,char *argv[])
{
	
	num=atoi(argv[1]);
	if(argc!=num+2) {printf("invalid input\n");exit(0);}
	
	for(int i=0;i<num;++i)
	{
		arr[0][i]=atoi(argv[i+2]);
		arr[1][i]=atoi(argv[i+2]);
	}
	int order[]={1,0};//1-asc 0-desc
	
	pthread_t tid[2];
	pthread_attr_t attr[2];
	pthread_attr_init(&attr[0]);
	pthread_attr_init(&attr[1]);
	pthread_create(&tid[0],&attr[0],runner,&order[0]);//ascending sort
	pthread_create(&tid[1],&attr[1],runner,&order[1]);//descending sort
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	return 0;
}

void *runner (void *param)
{
	int *order=(int *)param;
	for (int i = 1; i < num; i++) 
  {  
    int key = arr[*order][i];  
    int j = i - 1;  
  
    while (j >= 0 && ((1-*order)*(key-arr[*order][j])+(*order)*(arr[*order][j]-key))>0) 
    {  
      arr[*order][j + 1] = arr[*order][j];  
      j = j - 1;  
  	}  
    arr[*order][j + 1] = key;  
 	}  
	char ord[15];
	if(*order==1)
		strcpy(ord,"ascending");
	else
		strcpy(ord,"descending");
	printf("%s order\n",ord);
	for(int i=0;i<num;++i)
	printf("%d ",arr[*order][i]);
	printf("\n");
}
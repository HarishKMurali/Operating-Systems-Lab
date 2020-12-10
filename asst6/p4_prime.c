#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX_THREADS 4
void *runner(void* param);
int num;
int main(int argc,char *argv[])
{
	num=atoi(argv[1]);
	if(argc!=2) {printf("invalid input\n");exit(0);}

	for(int i=2;i<num;i+=MAX_THREADS)
	{
		pthread_t tid[MAX_THREADS];
		int temp[MAX_THREADS];
		for(int j=0;j<MAX_THREADS&&j<num-i;++j)
			temp[j]=i+j;
		for(int j=0;j<MAX_THREADS&&j<num-i;j++)
		{
			pthread_create(&tid[j],NULL,runner,&temp[j]);
		}
		for(int j=0;j<MAX_THREADS&&j<num-i;j++)
		pthread_join(tid[j],NULL); 

	}
	return 0;
}

void *runner(void* param)
{
	int *n=(int*)param;
	int flag=1;
	for(int i=2;i<*n;++i)
	{
		if(*n%i==0)
		{	
			flag=0;
			pthread_exit(0);
		}
	}
	if(flag==1)
		printf("%d\n",*n);
	pthread_exit(0);
}
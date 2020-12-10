#include <pthread.h> 
#include <stdio.h> 
#include<stdlib.h>
int sum; /* this data is shared by the thread(s) */ 
#define MAX_THREADS 10
void *runner (void *param); /* the thread */
int power(int a,int b ){
    int pow=1;
    while(b){
        pow*=a;
        b--;
    }
    return pow;
}

int main(int argc,char *argv[])
{
	if(argc!=3) {printf("invalid input\n");exit(0);}
	int lnum=atoi(argv[1]),hnum=atoi(argv[2]);
	//int sum[1000]={0};
	printf("The armstrong numbers in the givrn range:\n");
	for(int i=lnum;i<hnum;i+=MAX_THREADS)
	{
		pthread_t tid[MAX_THREADS];
		pthread_attr_t attr[MAX_THREADS];
        int temp[MAX_THREADS];
        for(int j=0;j<MAX_THREADS;++j)
		{
            pthread_attr_init (&attr[j]);
            temp[j]=i+j;
		    pthread_create(&tid[j], &attr[j], runner, &temp[j]);
        }
        for(int j=0;j<MAX_THREADS;++j)
		{
		    pthread_join(tid[j], NULL);
        }
	}
	return 0;
}
void *runner( void *param)
{

    int *num= (int *) param;

    int c=0,temp=*num;
    while(temp){
        temp=temp/10;
        c++;
    }
    temp=*num;
    sum=0;
    while(temp){
        int x=temp%10;
        sum+=power(x,c);
        temp=temp/10;
    }
		if(sum==*num)
		printf("%d\n",*num);

    pthread_exit(0);
}


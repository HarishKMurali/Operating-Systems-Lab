#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void *runner(void* param);
int fib[2];
int threadno=-1;
int num;
int main(int argc,char *argv[])
{
	num=atoi(argv[1]);
	if(argc!=2) {printf("invalid input\n");exit(0);}
	
	printf("0\n1\n");
	for(int i=2;i<num;++i)
	{
		pthread_t tid1,tid2;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		int temp1=i-1,temp2=i-2;
		pthread_create(&tid1,NULL,runner,&temp1);
		pthread_create(&tid2,NULL,runner,&temp2);
		pthread_join(tid1,NULL);
		pthread_join(tid2,NULL);
		printf("%d\n",fib[0]+fib[1]);
		threadno=-1;
	}
	return 0;
}
void *runner(void* param)
{
	int *n=(int*)param;
	threadno++;
	//printf("%d$",*n);
	int a = 0, b = 1, c, i; 
  if( *n == 0) 
    fib[threadno]=0;
	else
  {for (i = 2; i <= *n; i++) 
  { 
     c = a + b; 
     a = b; 
     b = c; 
  } 
  fib[threadno]=b;
	}
	//printf("%d %d**",threadno,fib[threadno]);
	
	pthread_exit(0);
}

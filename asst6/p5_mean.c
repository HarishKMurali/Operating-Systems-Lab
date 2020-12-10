#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdlib.h>

void *runner(void* param);
int num,arr[20];

void swap(int *p,int *q) 
{
   int t;
   
   t=*p; 
   *p=*q; 
   *q=t;
}

void sort(int a[],int n) 
{ 
   int i,j,temp;

   for(i = 0;i < n-1;i++) {
      for(j = 0;j < n-i-1;j++) {
         if(a[j] > a[j+1])
            swap(&a[j],&a[j+1]);
      }
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
	sort(arr,num);
	pthread_t tid[3];
	int temp[]={0,1,2};
	pthread_create(&tid[0],NULL,runner,&temp[0]);
	pthread_create(&tid[1],NULL,runner,&temp[1]);
	pthread_create(&tid[2],NULL,runner,&temp[2]);

	pthread_join(tid[0],NULL); 
	pthread_join(tid[1],NULL); 
	pthread_join(tid[2],NULL); 

	return 0;

}

void *runner(void * param)
{
	int *n=(int*)param;
	switch(*n)
	{
		case 0:	{float sum=0;
						for(int i=0;i<num;++i)
							sum+=arr[i];
						float mean=sum/num;
						printf("mean is %f\n",mean);
						break;}
		
		case 1:	{int median=arr[(num+1) / 2 - 1];
						printf("median is %d\n",median);
						break;}
		
		case 2: {int t=arr[num-1]+1;
						int *count=(int *)malloc(t*sizeof(int));
    				for (int i = 0; i < t; i++) 
        			count[i] = 0; 
  
    			  for (int i = 0; i < num; i++) 
        			count[arr[i]]++; 
  					int mode = 0; 
    				int k = count[0]; 
    				for (int i = 1; i < t; i++) 
						{ 
        			if (count[i] > k) 
							{ 
            		k = count[i]; 
            		mode = i; 
        			} 
   					} 
						printf("mode is %d\n",mode);
						break;}
		default: break;
	}
}
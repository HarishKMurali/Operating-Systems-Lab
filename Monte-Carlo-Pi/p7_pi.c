#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX_THREADS 10
#define INTERVAL 300
int interval, i; 
double rand_x, rand_y, origin_dist, pi; 
int circle_points = 0, square_points = 0; 

void *runner(void* param);

int main(int argc,char *argv[])
{
	srand(time(NULL));
	
	for (i = 0; i < (INTERVAL * INTERVAL); i+=MAX_THREADS)
	{
		pthread_t tid[MAX_THREADS];
		//int temp[MAX_THREADS]={0};
		for(int j=0;j<MAX_THREADS;++j)
			pthread_create(&tid[j],NULL,runner,NULL);
		for(int j=0;j<MAX_THREADS;++j)
			pthread_join(tid[j],NULL);
	}
	printf("interval is %d\nnumber of threads %d\n",INTERVAL,MAX_THREADS); 
	printf("pi value is %lf\n",pi);
	return 0;
}

void* runner(void* param)
{
	rand_x = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
  rand_y = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
  // Distance between (x, y) from the origin 
	origin_dist = rand_x * rand_x + rand_y * rand_y; 
  // Checking if (x, y) lies inside the define circle with R=1 
  if (origin_dist <= 1) 
    circle_points++; 
  // Total number of points generated 
	square_points++; 
	// estimated pi after this iteration 
  pi = (double)(4 * circle_points) / square_points; 
}

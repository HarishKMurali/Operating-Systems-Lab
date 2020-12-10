#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include<unistd.h>
#include<stdlib.h>

int elves=0,reindeer=0;
sem_t mutex;
sem_t santasem,reindeersem,elfsem;

pthread_t *CreateThread(void *(*f)(void *), void *a)
{
	pthread_t *t = malloc(sizeof(pthread_t));
	
	int ret = pthread_create(t, NULL, f, a);
	
	return t;
}

void* Santa(void* param)
{
	printf("inside santa!\n");
	while(1)
	{
		sem_wait(&santasem);
		sem_wait(&mutex);
		if(reindeer>=9)
		{
			printf("Sleigh prepared! Happy Christmas!\n");
			for(int i=0;i<9;++i)
				sem_post(&reindeersem);
			reindeer=0;
		}
		else if(elves==3)
			printf("Santa is helping elves\n");
		sem_post(&mutex);
	}
	pthread_exit(0);
}

void* Reindeer(void* param)
{
	int* id=(int *) param;
	int rid=*id;
	printf("[R]:reindeer number:%d came\n",rid);
	while(1)
	{
		sem_wait(&mutex);
		reindeer+=1;
		//printf("reindeer count:%d\n",reindeer);
		if(reindeer==9)
			sem_post(&santasem);
		sem_post(&mutex);
		sem_wait(&reindeersem);
		printf("[R] Reindeer %d getting hitched!\n",rid);
		sleep(20);
	}
	pthread_exit(0);
}

void* Elves(void *param)
{
	int* id=(int *) param;
	int rid=*id;
	//printf("[E]:elf number:%d came\n",rid);
	while(1)
	{
		sem_wait(&elfsem);
		sem_wait(&mutex);
		elves+=1;
		//printf("elves count:%d\n",elves);
		if(elves==3)
			sem_post(&santasem);
		else
			sem_post(&elfsem);
		sem_post(&mutex);
		printf("[E]:elf %d need help!\n",rid);
		sleep(10);

		sem_wait(&mutex);
		elves-=1;
		if(elves==0)
			sem_post(&elfsem);
		sem_post(&mutex);
		sleep(10);
	}
	pthread_exit(0);
}
int main()
{
	sem_init(&mutex, 0, 1);
	sem_init(&elfsem, 0, 1);
	sem_init(&santasem, 0, 0);
	sem_init(&reindeersem, 0, 0);
	int i=0;
	pthread_t tid,eid[9],rid[9];
	pthread_create(&tid,NULL,Santa,NULL);
	//pthread_t *santa_claus=CreateThread(Santa,0);
	int r[]={0,1,2,3,4,5,6,7,8};
	while(i<9)
	{
	 pthread_create(&rid[i],NULL,Reindeer,&r[i]);
	 pthread_create(&eid[i],NULL,Elves,&r[i]);
	 i++;
	}

	pthread_join(tid,NULL);
	for(int i=0;i<9;++i)
	{
		pthread_join(rid[i],NULL);
		pthread_join(eid[i],NULL);
	}
	return 0;
}
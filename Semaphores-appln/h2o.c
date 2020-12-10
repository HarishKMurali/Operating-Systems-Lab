#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h>

int hydrogen=0,oxygen=0,bcount=0;
sem_t mutex,hydroqueue,oxyqueue,b_mutex,sbarrier;

pthread_t o_thread,h_thread1,h_thread_2;



// void barrier_wait()
// {
//     sem_wait(&b_mutex);
//     bcount++;
//     sem_post(&b_mutex);

//     if(bcount==3)
//     {
//         sem_post(&sbarrier);
//     }

//     sem_wait(&sbarrier);
//     sem_post(&sbarrier);
// }

void bond()
{
    static int i=0;
    i++;
    if(i%3==0)
    {
        printf(" Water mol # %d created\n ",i/3);
    }
    sleep(2);
}

void * o_fn(void *arg)
{
    while(1)
    {
        sem_wait(&mutex);
        oxygen+=1;
        if(hydrogen>=2)
        {
            sem_post(&hydroqueue);
            sem_post(&hydroqueue); //increase by 2 so twice --> allows 2 H molecules
            hydrogen-=2;
            sem_post(&oxyqueue);
            oxygen-=1;
        }
        else
        {
            sem_post(&mutex);
        }
        
        sem_wait(&oxyqueue);
        printf(" one Oxygen is ready\n");
        bond();

        //barrier_wait();
        sem_post(&mutex); //release the lock acquired (this lock can be acquired by any thread and there has to be one unlock thats it) after 1 H20 molecule is done
    }
}

void *h_fn(void *arg)
{
    while(1)
    {
        sem_wait(&mutex);
        hydrogen+=1;

        if(hydrogen>=2 && oxygen>=1)
        {
            sem_post(&hydroqueue);
            sem_post(&hydroqueue);
            hydrogen-=2;
            sem_post(&oxyqueue);
            oxygen-=1;
        }
        else
        {
            sem_post(&mutex);
        }

        sem_wait(&hydroqueue);
        printf(" 1 Hydrogen molecule ready ");
        bond();

        //barrier_wait();        
    }
}

int main()
{
    sem_init(&b_mutex,0,1);
    sem_init(&sbarrier,0,0);
    sem_init(&mutex,0,1);
    sem_init(&oxyqueue,0,0);
    sem_init(&hydroqueue,0,0);

    pthread_create(&o_thread,NULL,o_fn,NULL);
    pthread_create(&h_thread1,NULL,h_fn,NULL);
    pthread_create(&h_thread_2,NULL,h_fn,NULL);

    while(1);

}
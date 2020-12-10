#include<stdio.h>
#include<sys/wait.h>
#include<pthread.h>
#include<string.h>
#define N 5
void *producer(void *param);
void *consumer(void *param);

struct dict
{
	char word[30];
	char mean1[30],mean2[30];
}buf[N];

int flag[]={0,0};
int turn=0;
char search_word[30];

int in=0,out=0,end=0;
int j=0;

void lock(int self)
{
    // Set flag[self] = 1 saying you want to acquire lock
    flag[self] = 1;
 
    // But, first give the other thread the chance to
    // acquire lock
    turn = 1-self;
 
    // Wait until the other thread looses the desire
    // to acquire lock or it is your turn to get the lock.
    while (flag[1-self]==1 && turn==1-self) ;
}
 
// Executed after leaving critical section
void unlock(int self)
{
    // You do not desire to acquire lock in future.
    // This will allow the other thread to acquire
    // the lock.
    flag[self] = 0;
}


int main(int argc,char * argv[])
{	
	pthread_t tid[2];
	strcpy(search_word,argv[1]);
	//strcpy(search_word,"book");
	pthread_create(&tid[0],NULL,producer,NULL);
	pthread_create(&tid[1],NULL,consumer,NULL);
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	return 0;
}


void *producer(void *param)
{
	int i=0;
	FILE *fptr=fopen("dict.txt","r");
	while(1)
	{
			
		lock(0);
		j=0;
		while(j<5)
		{
			//printf("@\n");
			char ch;
			char word[20];
			int k=0;
			
			while((ch=fgetc(fptr))!=',')
			{
				buf[j].word[k++]=ch;
			}
			buf[j].word[k]='\0';
			k=0;
			while((ch=fgetc(fptr))!=',')
			{
				buf[j].mean1[k++]=ch;
			}
			buf[j].mean1[k]='\0';
			k=0;
			while((ch=fgetc(fptr))!='\n')
			{
				if(ch==EOF)
				{
					buf[j].mean2[k]='\0';
					end=1;
					unlock(0);
					fclose(fptr);
					return NULL;
				}
				buf[j].mean2[k++]=ch;
			}
			buf[j].mean2[k]='\0';
			j++;
		
		}
		int k;
				
		++i;
		unlock(0);
	}
	
	pthread_exit(0);
}

void *consumer(void *param)
{
	int i=0;

	while(1)
	{
				
		lock(1);
		//printf("cons");
		int k=0;
		while(k<j)
		{
			//printf("#");
			if(strcmp(buf[k].word,search_word)==0)
			{
				printf("Word found:\n");
				puts(buf[k].word);
				printf("Meaning 1:\n");
				puts(buf[k].mean1);
				printf("Meaning 2:\n");
				puts(buf[k].mean2);
				unlock(1);
				return NULL;
			}
			k++;
		}
		
		++i;
		if(end==1)
		{
			printf("Word not found!\n");
			return NULL;
		}
		unlock(1);
		
	}

	pthread_exit(0);
}

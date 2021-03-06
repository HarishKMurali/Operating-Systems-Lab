#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int parl_fib (int n){

	if(n == 1){
		return 0;
	}
	if(n == 2){
		return 1;
	}
	else{
		int fib_a=0, fib_b=0;

		pid_t child1 = vfork();
		if(child1 == 0){
			fib_a = parl_fib(n-1);
			exit(0);
		}
		else{
			pid_t child2 = vfork();
			if(child2 == 0){
				fib_b = parl_fib(n-2);
				exit(0);
			}
			else{
				wait(NULL);
				return fib_a + fib_b;
			}
		}
		
	}

}

int main (int argc,char *argv[])
{
	if(argc!=2) {printf("invalid input\n");exit(0);}
	int n=atoi(argv[1]);

	for(int i=1;i<=n;++i)
	printf("%d\n", parl_fib(i));
	return 0;

}
#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sig_handler(int signum){
        printf("\n inside handler");
      	signal(SIGINT, SIG_DFL);
}

int main (){
        signal(SIGINT, sig_handler);
        for(int i=0; ; i++){
                printf("%d: Inside main\n", i);
                sleep(1);
        }
        return 0;
}
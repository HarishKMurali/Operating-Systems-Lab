# include <stdio.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>
int main ()
{
pid_t pid; // this is to use the pid data type – relevant headers above
pid = fork();
if (pid == 0)
execlp("ls", "ls", NULL); // child image is now ls command
else
{
wait (NULL); // parent waits for the child to complete execn.
printf("Parent Process gets the control \n");
printf ("Parent Has waited for Child to Complete\n");
}
}
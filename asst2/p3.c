#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main ()
{
printf("This will be printed ?. level0\n");
fork();
printf("This will be printed ?. level1\n");
fork();
printf("This will be printed ? .level2\n");
fork();
printf("This will be printed ? level3\n");
return 0;
}
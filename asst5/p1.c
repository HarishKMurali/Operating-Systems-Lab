#include<stdio.h> 
#include<unistd.h> 
#include<string.h>

char *strrev(char *str)
{
    if (!str || ! *str)
        return str;

    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}
int main() 
{ 
	int pipefds1[2], pipefds2[2]; 
	int returnstatus1, returnstatus2; 
	int pid; 
	char parentwrite[20];// = "string"; 
	 
	char readmessage[20]; 
	returnstatus1 = pipe(pipefds1); 
	if (returnstatus1 == -1) 
	{
	printf("Unable to create pipe I \n"); 
	return 1;
	} 
	returnstatus2 = pipe(pipefds2); 
	if (returnstatus2 == -1)
	{
		printf("Unable to create pipe 2 \n"); 
		return 1; 
	} 
	pid = fork(); 
	if (pid > 0) // Parent process 
	{ 
		close(pipefds1[0]); // Close the unwanted pipel read side 
		close(pipefds2[1]); // Close the unwanted pipe2 write side 
		printf("\nEnter string to be reversed:\n");
		gets(parentwrite);
		printf("In Parent: Writing to pipe I - Message is %s\n",parentwrite); 
		write(pipefds1[1], parentwrite,sizeof(parentwrite)+1); 
		read(pipefds2[0], readmessage, sizeof(readmessage)); 
		printf("In Parent: Reading from pipe 2 - Reversed string is %s\n", readmessage); 
	}
	else 
	{ 
		close(pipefds1[1]); // Close the unwanted pipel write side 
		close(pipefds2[0]); // Close the unwanted pipe2 read side 
		read(pipefds1[0], readmessage, sizeof(readmessage)); 
		printf("In Child: Reading from pipe I – Message is %s\n", readmessage); 
		char *reverse=strrev(readmessage);
		printf("In Child:Writing to pipe 2 – Message is %s\n",reverse); 
		write(pipefds2[1], reverse,sizeof(reverse)+1); 
		return 0; 
	} 
}
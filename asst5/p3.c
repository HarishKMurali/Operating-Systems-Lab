#include<stdio.h> 
#include<unistd.h> 
#include<string.h>
#include<stdlib.h>
int main() 
{ 
	int pipefds1[2], pipefds2[2]; 
	int returnstatus1, returnstatus2; 
	int pid; 
	char parentwrite[20];// = "string"; 
	 
	char readmessage[20]; 

	printf("\nEnter string:\n");
	char s1[20],s2[20];
	gets(s1);
	int b,e;
	printf("\nEnter indices:\n");
	scanf("%d %d",&b,&e);
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
		printf("In Parent: Writing to pipe I - string is %s\n",s1); 
		write(pipefds1[1], s1,sizeof(s1)+1);
		
		read(pipefds2[0], s2, sizeof(s2)); 
		strcat(s1,s2);
		printf("In Parent: Reading from pipe 2 - sub string is %s\n", s2); 
		 
		
	}
	else 
	{ 
		close(pipefds1[1]); // Close the unwanted pipel write side 
		close(pipefds2[0]); // Close the unwanted pipe2 read side 
		//printf("\nEnter string2:\n");
		//char s2[20];
		read(pipefds1[0],readmessage, sizeof(readmessage)); 
		printf("In Child: Reading from pipe I – string is %s\n", readmessage);
		
		if(b>e)
		{
			printf("wrong indices\n");
			exit(0);
		}
		else if(e>strlen(readmessage))
		{
			printf("wrong indices\n");
			exit(0);			
		}
		
		
		int i;
		for(i=b;i<=e;++i)
		s2[i-b]=readmessage[i];
		s2[i-b]='\0';
		printf("In Child:Writing to pipe 2 – sub string is %s\n",s2); 
		write(pipefds2[1], s2,sizeof(s2)+1); 
		 
		
		return 0; 
	} 
}
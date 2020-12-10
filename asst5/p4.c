#include<stdio.h> 
#include<unistd.h> 
#include<string.h>

void strrev(char *str)
{
    if (!str || ! *str)
        return;

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
    return;
}

int stringcompare(char *a,char *b)  
{  
   int flag=0;  
    while(*a!='\0' && *b!='\0')  // while loop  
    {  
        if(*a!=*b)  
        {  
            flag=1;  
        }  
        a++;  
        b++;  
    }  
      
    if(flag==0)  
    return 0;  
    else  
    return 1;  
}

int main() 
{ 
	int pipefds1[2], pipefds2[2]; 
	int returnstatus1, returnstatus2; 
	int pid; 
	char parentwrite[20];
	printf("\nEnter string to check if palindrome or not:\n");
	gets(parentwrite);
	 
	
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
		char readmessage[40]; 
		printf("In Parent: Writing to pipe I - Message is %s\n",parentwrite); 
		write(pipefds1[1], parentwrite,sizeof(parentwrite)+1); 
		read(pipefds2[0], readmessage, sizeof(readmessage)); 
		printf("In Parent: Reading from pipe 2 -%s\n", readmessage); 
	}
	else 
	{ 
		close(pipefds1[1]); // Close the unwanted pipel write side 
		close(pipefds2[0]); // Close the unwanted pipe2 read side 
		char readmessage[40]; 
		read(pipefds1[0], readmessage, sizeof(readmessage)); 
		printf("In Child: Reading from pipe I – Message is %s\n", readmessage); 
		char message[30];
		strcpy(message,readmessage);
		strrev(readmessage);
			
		char result[40];
		if((stringcompare(message,readmessage))!=0)
			strcpy(result,"The string is not palindrome!");
		else
			strcpy(result,"The string is palindrome!");

		printf("In Child:Writing to pipe 2 – Message is %s\n",result); 
		write(pipefds2[1], result,sizeof(result)+1); 
		//printf("%s",result);
		return 0; 
	} 
}
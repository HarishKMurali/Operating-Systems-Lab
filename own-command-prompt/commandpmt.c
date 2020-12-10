#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
//#include<conio.h>
#include<sys/wait.h>
#include<string.h>

struct Node  
{  
    char ** data; 
		int argc; 
    struct Node* link;  
}history;  
  
struct Node* top=NULL; 
void push(char* data[],int argc)  
{  
      
    // Create new node temp and allocate memory  
    struct Node* temp;  
    temp = (struct Node*)malloc(sizeof(struct Node));  
  
    // Check if stack (heap) is full.  
    // Then inserting an element would  
    // lead to stack overflow  
    if (!temp) 
    {  
        printf("\nHeap Overflow");  
        exit(1);  
    }  
  
    // Initialize data into temp data field  
    temp->data = data;  
		temp->argc=argc;
  
    // Put top pointer reference into temp link  
    temp->link = top;  
  
    // Make temp as top of Stack  
    top = temp;  
		
}  

void display(char *c[])  
{  
    struct Node* temp;  
		int h=atoi(c[0]);
    // Check for stack underflow  
    if (top == NULL) 
    {  
        printf("\nStack Underflow");  
        exit(1);  
    }  
    else 
    {  
        temp = top;
				int j=0;  
        while (temp != NULL && j<h) 
        {  
						printf("%d.",j+1);
            // Print node data  
						for(int i=0;i<temp->argc;++i)
            printf("%s ",temp->data[i]);  
						printf("\n");
						j++;
  
            // Assign temp link to temp  
            temp = temp->link;  
        }  
    }  
}  


void getcommand(char *cmd, char *args[],int argc)
{
    int i;
    char *c,*p;
		//c=p=NULL;
    for(i=0;i<=argc;i++)
     {   args[i]=malloc(100);
		if (args[i] == NULL) { 
        printf("Memory not allocated.\n");
        exit(0); 
    } 
		
		 }
    i=0;
    p=&args[0][0];
    for(c=cmd;*c!='\0';c++)
    {
        if(*c!=' ')
        {
            *p=*c;
            p++;
        }
        else
        {
            *p='\0';
            i++;
            p=&args[i][0];
        }
    }
    *p='\0';
    i++;
    args[i]=NULL;
    return;

}

int main()
{
	//textcolor(RED);
	printf("\033[0;31m"); 
	printf("---------------------------------\n");
	printf("\t\tMY COMMAND PROMPT\n");
	printf("----------------------------------\n");


	while(1)
	{
		char str[100],buf[50];
		printf("\033[1;32m");
		printf("my-cmd-pmt:");
		getcwd(buf,50);
		printf("\033[1;34m");
		printf("%s@",buf);
		printf("\033[0;32m");
		gets(str);
		int argc=1;
    for(int i=0;i<strlen(str);++i)
        if(str[i]==' ')
            argc++;
		//printf("%d\n",argc);
		char **argv=(char**)malloc(sizeof (char *)*(argc+1));
		if (argv == NULL) { 
        printf("Memory not allocated.\n"); 
        exit(0); 
    } 
		//argv=NULL;
		//printf("%d\n",argc);
		getcommand(str,argv,argc);
		
		//++argc;
		//*argv[argc]=NULL;
		/* for(int i=0;i<=argc;++i)
		{
			printf("%s",argv[i]);
		} */
		//char *const arg[]=argv;
		push(argv,argc);
		//if(strcmp(argv[0],"cd")==0)
		//changedir(argv);
		if(argv[0][0]=='!')
		{
		char *ch[1];
		ch[0]=&argv[0][1];
		display(ch);
		}
		else if(strcmp(argv[0],"exit")==0)
		{
			
			free(argv);
			
			exit(0);
		}
		else
		{
		pid_t pid=fork();
		
		if(pid==0)
		{
		execvp(argv[0],argv);
		printf("Please check your command.Can't be executed!\n");
		exit(0);
		}
		else if(pid>0)
		wait(NULL);
		}
		printf("\n");
	}

	return 0;
}
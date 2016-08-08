#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include<unistd.h>
#include<strings.h>
#include<stdlib.h>
#include<malloc.h>
#include<ctype.h>
#include<string.h>
int countTokens(char* str,char* delim);
void executeCommand(char* buf);
void execDelims(char* buf,char* delim);
void pipexec(char* buf);
void trim(char* str);
void trim(char* str){
        int i=strlen(str)-1;
         while(i>=0 && isspace(str[i])){//remove \n character
                        str[i]='\0';
                        i--;
                }

        }

int main(void)
{
 char buf[1024];
 pid_t pid;
 int status;
 printf("%% ");
 while (fgets(buf,1024,stdin) != NULL)
 {
   trim(buf);
  // buf[strlen(buf) -1] = 0;  //remove the last character. Important!
//	fprintf(stderr,"%s",buf);
	if(!strcmp(buf,"q"))
		break;
   if ((pid = fork()) <0)
    printf("fork error");
   else if (pid == 0) 
    { /* child */
		int i=0;
		while(buf[i]!='\0')
		{
			if(buf[i]=='|' && buf[i+1]=='|')
				break;
			i++;
		}
		if(buf[i]!='|')
		{
			executeCommand(buf);
		}
	
		else
		{
			pipexec(buf);
		}
		printf("couldn't execute: %s", buf);
	     exit(127);
    }
   /* parent */ 
 if ( (pid = waitpid(pid, &status, 0)) < 0)
  printf("waitpid error");  
 fprintf(stderr,"%% ");
 }
 exit(0);
}
void pipexec(char* buf)
{
		char* command[2];
		char* temp = malloc(sizeof(char) * strlen(buf));
		strcpy(temp,buf);
		int ppid;
		int status;
//		fprintf(stderr,"going inside\n");

                              //int number =0;
                                //char* ptr;
				int j=0;
		char* t=malloc(sizeof(char) * strlen(buf));
				while(buf[j]!='|')
				{
                        	        	//t[j]=buf[j];
					j++;
				}
				strncpy(t,buf,j);
				command[0]=t;
				command[1] = strstr(temp,"||");
				//trim(command[1]);
				int l=(strlen(t)+strlen(command[1]))-strlen(buf);
				if(l>0)
				{
					command[1][strlen(command[1])-l]='\0';
				}

                        int PA[2];
                        pipe(PA);
                        if((ppid=fork())==0)
                        {
                        //      close(PA[0]);
                                dup2(PA[1],1);
                                close(PA[0]);
                                close(PA[1]);
                                executeCommand(command[0]);


                        }
                        dup2(PA[0],0);
                        close(PA[1]);
                        close(PA[0]);
                        if(countTokens(temp,"||")>2)
                       {
				pipexec(command[1]+2);


                        }
                        else
			{
                                executeCommand(command[1]+2);
			}
                         if ( (ppid = waitpid(ppid, &status, 0)) < 0)
                                  printf("waitpid error");
}
void executeCommand(char* buf)
{
//      fprintf(stderr,"executing command");

//fprintf(stderr,"'%s'",buf);
  int i=0;
        while(buf[i]!='\0')
        {
                if(buf[i]==' ')
                        break;
                i++;
        }
        if(buf[i]==' ')
        {

		execDelims(buf," ");
		
	}
	else
		if(execlp(buf,buf,(char *) 0)<0)
			fprintf(stderr,"%s failed\n",buf);
}
void execDelims(char* buf,char* delim)
{
	int size;
	size=countTokens(buf,delim)+1;
        char* command[size];
        int number=0;
 	char* ptr;
         command[0] = strtok(buf,delim);
        while((ptr = strtok(NULL, delim)) != NULL)
           {
            number++;
            command[number] = ptr;
           }
		
                command[number+1]=(char*) NULL;
		fprintf(stderr," '%s' '%s'  ",command[0],command[1]);
                if(execvp(command[0],command)<0)
                        fprintf(stderr,"%s failed\n",command[0]);

                

}
int countTokens(char* str,char* delim)
{
	int i=0;
	char* n;
	while((n=strstr(str,delim))!=NULL)
	{
		i++;
		str=n+strlen(delim);

	}
	return i+1;

	
	
} 


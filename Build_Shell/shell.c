#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>

void handlerControl_C(int signal){
    printf("\nYou typed Control-C!\n");
}

int main() {
char prompt[100]="hello:";

char var_read[50]="";
   
char command[1024];
char originalCommand[1024];
char *token;
int i;
char *outfile;

char last_command[100]="";
int fd, amper, redirect,append=0,useLastCommend=0,input=0, piping,retid, status, argc1;
int fildes[2];
char *argv1[10], *argv2[10];

signal(SIGINT,handlerControl_C);
while (1)
{
     

    if(!useLastCommend){
        printf("%s ",prompt);
        fgets(command, 1024, stdin);
        command[strlen(command) - 1] = '\0';
        //strcpy(last_command,command);
    }else{
        strcpy(command,last_command);
        useLastCommend=0;
        memset(last_command,0,sizeof(last_command));
    }
  
    piping = 0;

    /* parse command line */
    i = 0;
    token = strtok (command," ");
    while (token != NULL)
    {
        argv1[i] = token;
        token = strtok (NULL, " ");
        i++;
        if (token && ! strcmp(token, "|")) {
            piping = 1;
            break;
        }
    }
    argv1[i] = NULL;
    argc1 = i;

    /* Is command empty */
    if (argv1[0] == NULL)
        continue;
    
    if(argc1 >=3 && !strcmp(argv1[0],"prompt") && !strcmp(argv1[1],"=")) {
            strcpy(prompt,argv1[2]);                     // exe 3       //  we end with no more command
            continue;
    }   
    if(argc1 >=2 && !strcmp(argv1[0],"echo") && !strcmp(argv1[1],"$?")) {
            printf("%d\n",status);                     // exe 5    - print status 
            continue;
    } 
    if(argc1 >=2 && !strcmp(argv1[0],"echo") && (argv1[1][0]=='$')) {
            sprintf(last_command,"echo $%s",argv1[1]);                     // exe 11   - print shell variable 
             
            continue;
    } 
    if(argc1 >=2 && !strcmp(argv1[0],"cd")) {
            chdir(argv1[1]);                   // exe 6 
            continue;
    } 
    if(argc1 >=1 && !strcmp(argv1[0],"!!")) {
            useLastCommend=1;                   // exe 7 
            continue;
    } 
    if(argc1 >=2 && !strcmp(argv1[0],"read")) {                // exe 12 read - fix     
        
    } 
    if(argc1 >=3 && !strcmp(argv1[1],"=") && (argv1[0][0]=='$') ) {                // exe 11 save variables
         memset(last_command,0,sizeof(last_command));
         sprintf(last_command,"export %s=%s",&argv1[0][1], argv1[2]);
         useLastCommend=1;  
         printf("%s ,arg0 %s ,arg1 %s ,arg2 %s", last_command,argv1[0],argv1[1],argv1[2]) ;        
         continue;
    } 

    if(argc1 >=1 && !strcmp(argv1[0],"quit")) {
        exit(0);                      // exe 8 
    } 

    /* Does command contain pipe */
    if (piping) {
        i = 0;
        while (token!= NULL)
        {
            token = strtok (NULL, " ");
            argv2[i] = token;
            i++;
        }
        argv2[i] = NULL;
    }
    
    /* Does command line end with & */ 
    if (! strcmp(argv1[argc1 - 1], "&")) {
        amper = 1;
        argv1[argc1 - 1] = NULL;
        }
    else 
        amper = 0; 
    //printf("%d, %s, %s ,%s\n",argc1,argv1[0],argv1[1],argv1[2]);
    if (argc1 > 1 && !strcmp(argv1[argc1 - 2], ">")) {
        redirect = 1;
        argv1[argc1 - 2] = NULL;
        outfile = argv1[argc1 - 1];
        //printf("1:%d ,2: %d,3:%s ,4:%s\n",redirect,argc1,argv1[0], outfile);
        
        }
    else {
        redirect = 0;
        //printf("2::%d, %s, %s ,%s\n",argc1,argv1[0],argv1[1],argv1[2]); 
        // Append
        if (argc1 > 1 && ! strcmp(argv1[argc1 - 2], ">>")) {
        append = 1;
        argv1[argc1 - 2] = NULL;
        outfile = argv1[argc1 - 1];
        }
        else 
        {
            append = 0;
            // Input
            if (argc1 > 1 && ! strcmp(argv1[argc1 - 2], "<")) {
            input = 1;
            argv1[argc1 - 2] = NULL;
            outfile = argv1[argc1 - 1];
            }
            else 
            input = 0;
        }
    }
           /* for commands not part of the shell command language */ 

    if (fork() == 0) { 
        /* redirection of IO ? */
        if (redirect) {
            fd = creat(outfile, 0660); 
            printf("outfile :%s ",outfile);
            close (STDOUT_FILENO) ; 
            dup(fd); 
            close(fd); 
            /* stdout is now redirected */
        } 
        if (append) {
            fd = open(outfile, O_WRONLY|O_CREAT|O_APPEND, 0660); // check if works  and not -1
            close (STDOUT_FILENO); 
            dup(fd); 
            close(fd); 
            /* stdout is now appended */
        } 
        if (input) {
            fd = open(outfile, O_RDONLY, 0660); // check if works  and not -1
            close (STDIN_FILENO); 
            dup(fd); 
            close(fd); 
            /* stdin is now redirected */
        } 
        if (piping) {
            pipe (fildes);

            if (fork() == 0) { 
                /* first component of command line */ 
                close(STDOUT_FILENO); 
                dup(fildes[1]); 
                close(fildes[1]); 
                close(fildes[0]); 
                /* stdout now goes to pipe */ 
                /* child process does command */ 
                execvp(argv1[0], argv1);
            } 
            /* 2nd command component of command line */ 
            close(STDIN_FILENO);
            dup(fildes[0]);
            close(fildes[0]); 
            close(fildes[1]); 
            /* standard input now comes from pipe */ 
            execvp(argv2[0], argv2);
        } 
        else
            execvp(argv1[0], argv1);
    }
    /* parent continues over here... */
    /* waits for child to exit if required */
    if (amper == 0)
        retid = wait(&status);

    strcpy(last_command,command);
}
}

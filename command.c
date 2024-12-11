//
// Created by knn64 on 12/11/24.
//
//
// Created by ubuntu on 11/30/24.


#include <time.h>
#include "utils.h"
#define ERRFORK "Fork failed\n"

struct timespec start_time;
struct timespec end_time;

// A function that reads a given command and put it in a buffer
void prompt_read(char *cmd,int * argc,char *argv[]){
    int nb = (int) read(STDIN_FILENO, cmd, BUFMAXSIZE);
    cmd[nb-1] = '\0';
    int k=0;
    char *token = strtok(cmd, " ");// creating a slicer of the given buffer

    while(token != NULL && k<BUFMAXSIZE-1) {
        argv[k] = token;
        token = strtok(NULL, " ");//to the next argument
        k++;
    }
    argv[k] = NULL;
    *argc = k-1;
}



void exec_complex_cmd(int argc,char **cmd,int *status) {
    pid_t pid = fork();
    if (pid==-1) {// Test of the fork success
        write(STDERR_FILENO,ERRFORK,strlen(ERRFORK));
    }else if (pid == 0) {
        if (strcmp(cmd[0],"gettftp")==0)
        {
            cmd_gettftp(argc,cmd);
        }
        else if (strcmp(cmd[0],"puttftp")==0)
        {
            cmd_puttftp(argc,cmd);
        }
        else
        {
            execvp(cmd[0],cmd);
        }
        exit(EXIT_SUCCESS);
    }else {
        wait(status);
    }
}


//This function checks the status of the last executed process and give its time of execution
void check_status(int status) {
    char prompt[BUFMAXSIZE] = {0};

    if (WIFEXITED(status)) {
        snprintf(prompt,BUFMAXSIZE,"[exit:%d]",WEXITSTATUS(status));
        write(STDIN_FILENO,prompt,strlen(prompt));
    }else if (WIFSIGNALED(status)) {
        snprintf(prompt,BUFMAXSIZE,"[sign:%d]",WIFSIGNALED(status));
        write(STDIN_FILENO,prompt,strlen(prompt));
    }
}


int command_exit(char *cmd) {
    if (strcmp(cmd, "exit") == 0) {
        write(STDOUT_FILENO, ByeBye, strlen(ByeBye));
        return 1;
    }
    return 0;
}




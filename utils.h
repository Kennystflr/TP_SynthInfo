//
// Created by knn64 on 12/11/24.
//

#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

#define msg_welcome "Bienvenue dans le shell de VMmPo. \n Pour quitter, tapez 'exit'. \n "
#define msg_VMmPo "VMmPo"
#define pourcent "%%"
#define BUFMAXSIZE 1024
#define ByeBye "Bye bye....\n"

#include "tftp.h"


void print_prompt();
void welcome();
void print_pourcent();
int command_exit(char *cmd);
void prompt_read(char *cmd,int* argc,char ** argv);
void check_status(int status);
void exec_complex_cmd(int argc,char**,int*);
#endif //UTILS_H

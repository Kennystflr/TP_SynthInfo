//
// Created by knn64 on 12/11/24.
//
#include "utils.h"

void welcome() {
    write(STDOUT_FILENO, msg_welcome, strlen(msg_welcome));
}

void print_prompt() {
    write(STDOUT_FILENO, msg_VMmPo, strlen(msg_VMmPo));
}

void print_pourcent(){
    write(STDOUT_FILENO, pourcent, strlen(pourcent));
}

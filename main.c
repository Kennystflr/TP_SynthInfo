#include "utils.h"



int main()
{
    char command[BUFMAXSIZE] = {0};
    char * argv[BUFMAXSIZE] ;
    int argc = 0;
    int status = 0;
    struct timespec start_time;
    struct timespec end_time;

    welcome();
    print_prompt();
    print_pourcent();

    while(1) {
        prompt_read(command,&argc,argv);
        if (command_exit(command)==1){
            break;
        }
        exec_complex_cmd(argc,argv,&status);
        print_prompt();
        check_status(status);
        print_pourcent();
    }


}


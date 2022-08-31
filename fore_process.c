#include "headers.h"

void run_in_foreground(char** argument_list){

    pid_t fore_pid = fork();

    if (fore_pid < 0){
        perror("Could not create forked process");
    } else if (fore_pid == 0){
        if ( execvp(argument_list[0], argument_list) < 0){
            printf("Command not found\n");
        }
        exit(EXIT_SUCCESS);
    } else {

        time_t process_begin_clock = time(NULL);

        int process_status;
        waitpid(fore_pid,&process_status,WUNTRACED);

        time_t process_end_clock = time(NULL);
        process_exec_time = process_end_clock - process_begin_clock;
    }

}
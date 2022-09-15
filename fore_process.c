#include "headers.h"

void run_in_foreground(char** argument_list){

    pid_t fore_pid = fork();

    // starting timer
    time_t process_begin_clock = time(NULL);

    if (fore_pid < 0){
        perror("Could not create forked process");
        process_exec_time = 0;
        return;
    } else if (fore_pid == 0){
        if ( execvp(argument_list[0], argument_list) < 0){
            printf("Command not found\n");
        }
        exit(EXIT_SUCCESS);
    } else {
        is_foreground_running = 1;

        int process_status;
        waitpid(fore_pid, &process_status, WUNTRACED);

        is_foreground_running = 0;
    }

    // Ending process
    time_t process_end_clock = time(NULL);
    process_exec_time = process_end_clock - process_begin_clock;
}
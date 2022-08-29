#include "headers.h"

void run_in_background(char* command, ssize_t* tot_jobs, ssize_t* jobs_done){
    // INCOMPLETE
    pid_t child_pid = fork();
    if (child_pid < 0){
        perror("Child process initialization failed!");
        return;
    }

    if (child_pid != 0){
        tot_jobs++;
        printf("[%ld] %d\n", tot_jobs - jobs_done + 1, child_pid);
    }else{
        
        run_command(command);

        jobs_done++;
        exit(EXIT_SUCCESS);
    }
}
#include "headers.h"

void fg(char** arg_list, int arg_num){
    if (arg_num != 1){
        printf("Invalid number of arguments!\n");
        return;
    }

    int job_number = atoi(arg_list[0]);

    if (job_number < 1 || job_number > running_background_processes->size){
        printf("Invalid job number!\n");
        return;
    }

    int cur_num = 1;

    DLLNode cur_node = running_background_processes->start_node->next_node;
    while(cur_node != NULL && cur_num < job_number){
        cur_num++;
        cur_node = cur_node->next_node;
    }

    pid_t job_pid = cur_node->element->process_pid;

    // ignoring signals
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    // setting group pid
    setpgid(job_pid, getpgid(0));

    // making foreground process
    tcsetpgrp(STDIN_FILENO, job_pid);

    if (kill(job_pid, SIGCONT) < 0){
        perror("Could not send signal");
        delete_from_dll(running_background_processes, job_pid);
        // setting process specified by terminal again foreground
        tcsetpgrp(STDIN_FILENO, shell_pid);

        // returning to default signals
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        return;
    }

    waitpid(job_pid, NULL, WUNTRACED);

    delete_from_dll(running_background_processes, job_pid);

    // setting process specified by terminal again foreground
    tcsetpgrp(STDIN_FILENO, shell_pid);

    // returning to default signals
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}
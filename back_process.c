#include "headers.h"

BackProcess background_process_queue[1000];

void run_cmd_background(char* cur_command){
    char* argument_list[max_arg_length];
    char* old_argument = strdup(cur_command);
    int num_arguments;
    my_strtok(argument_list, &num_arguments, " \n\t", cur_command);
    run_in_background(argument_list);
}

void run_in_background(char** argument_list){

    pid_t back_pid = fork();

    if (back_pid < 0){
        perror("Could not create forked process");
    } else if (back_pid == 0){
        if ( execvp(argument_list[0], argument_list) < 0){
            printf("Background process - Command not found\n");
        }
        exit(EXIT_SUCCESS);
    } else {
        printf("[%ld] %d\n", ++background_process_num, back_pid);
        background_process_queue[background_process_num].process_pid = back_pid;
        background_process_queue[background_process_num].process_name = strdup(argument_list[0]);
    }
}
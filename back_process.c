#include "headers.h"
#include "back_process.h"

void run_back_background(char* cur_command){
    char* argument_list[max_arg_length];
    char* old_argument = strdup(cur_command);
    int num_arguments;
    my_strtok(argument_list, &num_arguments, " \n\t", cur_command);
    run_in_background(argument_list, num_arguments);
}

void run_in_background(char** argument_list, int argument_num){
    
    if (argument_num == 0){
        printf("syntax error near unexpected token `&`\n");
        return;
    }

    pid_t back_pid = fork();

    if (back_pid < 0){
        perror("Could not create forked process");
    } else if (back_pid == 0){
        if ( execvp(argument_list[0], argument_list) < 0){
            printf("\nBackground process - Command not found\n");
        }
        exit(EXIT_SUCCESS);
    } else {
        insert_dll(running_background_processes, back_pid, argument_list[0]);
        printf("[%ld] %d\n", running_background_processes->size, back_pid);
    }
    fflush(stdout);
}

void background_process_term(){

    int status;
    pid_t back_process = waitpid(-1, &status, WNOHANG);

    if (back_process > 0){
        DLLNode req_node = find_node(running_background_processes, back_process);

        printf("\n%s with pid %d exited ", req_node->element->process_name, req_node->element->process_pid);

        if (WIFEXITED(status)){
            printf("Normally\n");
            // fprintf(stderr, "Process: %s PID: %d -> exited with status %d\n", background_process_queue[i].process_name, background_process_queue[i].process_pid, WEXITSTATUS(status));
        } else {
            printf("Abnormally\n");
            // fprintf(stderr, "Process: %s PID: %d -> FAILED\n", background_process_queue[i].process_name, background_process_queue[i].process_pid);
        }

        delete_node(running_background_processes, req_node);
        prompt();
    }

    fflush(stdout);
}
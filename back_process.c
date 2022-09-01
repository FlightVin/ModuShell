#include "headers.h"
#include "back_process.h"

// BackProcess background_process_queue[1000];

// void run_cmd_background(char* cur_command){
//     char* argument_list[max_arg_length];
//     char* old_argument = strdup(cur_command);
//     int num_arguments;
//     my_strtok(argument_list, &num_arguments, " \n\t", cur_command);
//     run_in_background(argument_list);
// }

// void run_in_background(char** argument_list){

//     pid_t back_pid = fork();

//     if (back_pid < 0){
//         perror("Could not create forked process");
//     } else if (back_pid == 0){
//         if ( execvp(argument_list[0], argument_list) < 0){
//             printf("\nBackground process - Command not found\n");
//         }
//         exit(EXIT_SUCCESS);
//     } else {
//         printf("[%ld] %d\n", ++background_process_num, back_pid);
//         background_process_queue[background_process_num].process_pid = back_pid;
//         background_process_queue[background_process_num].process_name = strdup(argument_list[0]);
//     }
//     fflush(stdout);
// }

// void background_process_term(){
//     int processes_to_be_deleted[max_arg_length];
//     int num_deletion = 0;

//     int status;
//     pid_t back_process = waitpid(-1, &status, WNOHANG);
//     for (int i = 1; i<=background_process_num; i++){
//         if (back_process == background_process_queue[i].process_pid){
//             printf("\n%s with pid %d exited ", background_process_queue[i].process_name, background_process_queue[i].process_pid);
            
//             if (WIFEXITED(status)){
//                 printf("Normally\n");
//                 // fprintf(stderr, "Process: %s PID: %d -> exited with status %d\n", background_process_queue[i].process_name, background_process_queue[i].process_pid, WEXITSTATUS(status));
//             } else {
//                 printf("Abnormally\n");
//                 // fprintf(stderr, "Process: %s PID: %d -> FAILED\n", background_process_queue[i].process_name, background_process_queue[i].process_pid);
//             }
//             remove_from_queue(i);
//             prompt();
//             break;
//         }
//     }
//     fflush(stdout);
// }

// void remove_from_queue(int process_index){
//     background_process_num--;
//     for (int i = process_index; i <= background_process_num + 1; i++){
//         background_process_queue[i] = background_process_queue[i+1];
//     }
//     background_process_queue[background_process_num + 1].process_name = strdup("\0");
//     background_process_queue[background_process_num + 1].process_pid = -1;
// }

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
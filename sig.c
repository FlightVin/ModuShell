#include "headers.h"

void sig(char** arg_list, int arg_num){
    if (arg_num != 2){
        printf("Invalid number of arguments!\n");
        return;
    }

    int job_number = atoi(arg_list[0]);
    int signal_number = atoi(arg_list[1]);

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

    if (kill(cur_node->element->process_pid, signal_number) < 0){
        perror("Could not send signal");
    }
}
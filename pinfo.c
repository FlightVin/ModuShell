#include "headers.h"

void pinfo(char** argument_list, int num_arguments){
    pid_t cur_pid;

    if (num_arguments == 0){
        cur_pid = getpid();
    } else {
        cur_pid = atoi(argument_list[0]);
    }

    printf("pid : %d\n", cur_pid);

    // checking status file of pid
    char stat_path[max_str_len];
    sprintf(stat_path, "/proc/%d/stat", cur_pid);

    FILE* stat_file_stream = fopen(stat_path, "r");

    if (stat_file_stream == NULL){
        perror("Could not open file of process");
        return;
    }
}
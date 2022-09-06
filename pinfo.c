#include "headers.h"
#include "path.h"

void pinfo(char** argument_list, int num_arguments){
    pid_t cur_pid;

    if (num_arguments == 0){
        cur_pid = getpid();
    } else {
        cur_pid = atoi(argument_list[0]);
    }

    // checking status file of pid
    char file_path[max_str_len];
    sprintf(file_path, "/proc/%d/stat", cur_pid);

    FILE* stat_file_stream = fopen(file_path, "r");

    if (stat_file_stream == NULL){
        perror("Could not open proc/[PID]/stat file of process");
        return;
    }

    int virtual_memory_size, group_pid, fore_process_pid;
    char char_process_state;

    // getting required data from stat_file_name
    fscanf(stat_file_stream, "%d %*s %c %*s %d %*s %*s %d %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d", &cur_pid, &char_process_state, &group_pid, &fore_process_pid, &virtual_memory_size);

    printf("pid : %d\n", cur_pid);

    char process_state[3];
    sprintf(process_state, "%c", char_process_state);
    if (group_pid == fore_process_pid){ // checking if foreground process
        strcat(process_state, "+");
    }

    printf("process Status : %s\n", process_state);

    // virtual memory used in bytes
    printf("memory : %d {Virtual Memory}\n", virtual_memory_size);

    fclose(stat_file_stream);

    // opening exe
    sprintf(file_path, "/proc/%d/exe", cur_pid);

    char abs_exec_path[max_str_len];
    ssize_t exec_len = readlink(file_path, abs_exec_path, 1000);

    if (exec_len < 0){
        perror("Could not read link from stat/[PID]/exe");
        return;
    }

    abs_exec_path[exec_len] = '\0';

    char exec_path[max_str_len];
    relative_path(abs_exec_path, exec_path);
    printf("executable Path : %s\n", exec_path);
}
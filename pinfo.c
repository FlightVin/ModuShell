#include "headers.h"
#include "path.h"

void pinfo(char** argument_list, int num_arguments){
    pid_t cur_pid;

    if (num_arguments == 0){
        cur_pid = getpid();
    } else {
        cur_pid = atoi(argument_list[0]);
    }

    printf("pid : %d\n", cur_pid);

    // checking status file of pid
    char file_path[max_str_len];
    sprintf(file_path, "/proc/%d/stat", cur_pid);

    FILE* stat_file_stream = fopen(file_path, "r");

    if (stat_file_stream == NULL){
        perror("Could not open proc/[PID]/stat file of process");
        return;
    }

    // Reading pid from /proc/[pid]/stat
    int pid_from_file;
    fscanf(stat_file_stream, "%d", &pid_from_file);

    // Reading COMM - filename of executale from /proc/[pid]/stat
    char stat_exec_file_name[max_str_len];
    fscanf(stat_file_stream, "%s", stat_exec_file_name);

    // Reading state from /proc/[pid]/stat
    char char_process_state;
    fscanf(stat_file_stream, "%c", &char_process_state);
    // reading twice to remove intermediate character
    fscanf(stat_file_stream, "%c", &char_process_state);

    char process_state[3];
    sprintf(process_state, "%c", char_process_state);
    if (find_node(running_background_processes, cur_pid)){
        strcat(process_state, "+");
    }

    printf("process Status : %s\n", process_state);

    fclose(stat_file_stream);

    // opening statm
    sprintf(file_path, "/proc/%d/statm", cur_pid);
    FILE* statm_file_stream = fopen(file_path, "r");

    if (statm_file_stream == NULL){
        perror("Could not open proc/[PID]/statm file of process");
        return;
    }

    int virtual_memory_size;
    fscanf(statm_file_stream, "%d", &virtual_memory_size);

    printf("memory : %d {Virtual Memory}\n", virtual_memory_size);

    fclose(statm_file_stream);

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
#include "headers.h"

int compare_func(const void* a, const void* b){
    char* l = *((char**) a);
    char* r = *((char**) b);

    return strcmp(&l[12], &r[12]);
}

void jobs(char** arg_list, int arg_num){
    // parsing flags
    int r_flag = 0, s_flag = 0;

    for (int i = 0; i<arg_num; i++){
        if (arg_list[i][0] == '-'){
            for (int j = 1; j < strlen(arg_list[i]); j++){
                if (arg_list[i][j] == 'r'){
                    r_flag = 1;
                } else if (arg_list[i][j] == 's'){
                    s_flag = 1;
                } else {
                    printf("jobs: No support for flag '%c'. Ignoring and proceeding...\n", arg_list[i][j]);
                }
            }
        } else {
            printf("Invalid argument: %s\n", arg_list[i]);
            return;
        }
    }

    if (r_flag == 0 && s_flag == 0){
        r_flag = 1;
        s_flag = 1;
    }

    int process_num = 1, print_count = 0;
    char* print_list[max_arg_length];

    DLLNode cur_node = running_background_processes->start_node->next_node;

    while(cur_node != NULL){
        pid_t cur_pid = cur_node->element->process_pid;

        // checking status file of pid
        char file_path[max_str_len];
        sprintf(file_path, "/proc/%d/stat", cur_pid);

        FILE* stat_file_stream = fopen(file_path, "r");

        if (stat_file_stream == NULL){
            perror("Could not open proc/[PID]/stat file of process");
            return;
        }
        
        char char_process_state;

        // getting required data from stat_file_name
        fscanf(stat_file_stream, "%d %*s %c", &cur_pid, &char_process_state);

        fclose(stat_file_stream);

        if (char_process_state == 'S' && r_flag == 1){
            char temp_str[max_str_len];
            sprintf(temp_str, "[%d] Running %s [%d]", process_num, cur_node->element->process_name, cur_pid);
            print_list[print_count++] = strdup(temp_str);
        }


        if (char_process_state == 'T' && s_flag == 1){
            char temp_str[max_str_len];
            sprintf(temp_str, "[%d] Stopped %s [%d]", process_num, cur_node->element->process_name, cur_pid);
            print_list[print_count++] = strdup(temp_str);
        }

        process_num++;
        cur_node = cur_node->next_node;
    }

    if (print_count == 0) return;

    qsort(print_list, print_count, sizeof(print_list[0]), compare_func);

    for (int i = 0; i<print_count; i++){
        printf("%s\n", print_list[i]);
    }
}
#include "headers.h"
#include "path.h"
#include "ls.h"
#include "cmd.h"

void ls(char** passed_args, int num_args){
    char* dir_names[max_arg_length];
    size_t dir_num = 0;

    int l_flag = 0;
    int a_flag = 0;
    int no_dir_flag = 1;

    for (int i = 0; i<num_args; i++){
        if (passed_args[i][0] == '-'){
            for (int j = 1; j < strlen(passed_args[i]); j++){
                if (passed_args[i][j] == 'a'){
                    a_flag = 1;
                } else if (passed_args[i][j] == 'l'){
                    l_flag = 1;
                } else {
                    printf("ls: No support for flag '%c'. Ignoring and proceeding...\n", passed_args[i][j]);
                }
            }
        } else {

            no_dir_flag = 0;
            char correct_path[max_arg_length];
            absolute_path(passed_args[i], correct_path);

            DIR* dir_ret_value = opendir(correct_path);

            if (dir_ret_value){
                dir_names[dir_num++] = strdup(correct_path);
            } else {
                char error_string[max_str_len];
                sprintf(error_string, "ls: cannot access '%s'.", correct_path);
                perror(error_string);
            }
        }
    }

    // if dir_num == 0 && no_dir then access ~
    if (dir_num == 0){
        if (no_dir_flag){
            my_cwd();
            dir_names[dir_num++] = strdup(cur_dir);
        }else{
            return;
        }
    }

    // else
    do_ls(dir_names[0], l_flag, a_flag);
    for (int i = 1; i<dir_num; i++){
        printf("\n");
        do_ls(dir_names[i], l_flag, a_flag);
    }
}

int comparator(const void* a, const void* b){
    char* l = ((struct dirent*)a)->d_name;
    char* r = ((struct dirent*)b)->d_name;

    return strcasecmp(a, b);
}

// Test this - ls -al /mnt ~/dir1 ./dir1 ../C-shell/dir2 dir2 kjlsd

void do_ls(char* cur_dir, int l_flag, int a_flag){
    char relative_name[max_str_len];
    relative_path(cur_dir, relative_name);
    printf("%s:\n", relative_name);

    DIR* dir_stream = opendir(cur_dir);
    if (!dir_stream){
        char error_string[max_str_len];
        sprintf(error_string, "Could not open DIR* of '%s'.", cur_dir);
        perror(error_string);
        return;
    }

    struct dirent* dir_list[max_arg_length];
    size_t dir_num = 0;

    struct dirent* dir_struct = readdir(dir_stream);
    while(dir_struct != NULL){
        if (dir_struct->d_name[0] == '.'){
            if (a_flag == 1){
                dir_list[dir_num++] = dir_struct;
            }
        }else{
            dir_list[dir_num++] = dir_struct;
        }

        dir_struct = readdir(dir_stream);
    }

    qsort((void*)dir_list, dir_num, sizeof(dir_list[0]), comparator);

    if (l_flag == 0){
        for (int i = 0; i<dir_num; i++){
            color_print(dir_list[i]);
            printf(" ");
        }
        printf("\n");
    } else {

        for (int i = 0; i<dir_num; i++){

            char cur_path[max_str_len];
            strcpy(cur_path, cur_dir);
            strcat(cur_path, "/");
            strcat(cur_path, dir_list[i]->d_name);
            puts(cur_path);
        }
    }

    int close_ret_value = closedir(dir_stream);
    if (close_ret_value < 0){
        char error_string[max_str_len];
        sprintf(error_string, "Could not close DIR* of '%s'.", cur_dir);
        perror(error_string);
    }
}

void color_print(struct dirent* cur_ptr){
    if (cur_ptr->d_type == DT_DIR){
        printf(" \033[0;34m");
    } else if (cur_ptr->d_type == DT_REG){
        // To do executable cheking
    }
    printf("%s", cur_ptr->d_name);
    printf(" \033[0m");
}
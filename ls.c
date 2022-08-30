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
                dir_names[dir_num++] = passed_args[i];
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

// Test this - ls /mnt ~/dir1 ./dir1 ../C-shell/dir2 dir2 kjlsd

void do_ls(char* cur_dir, int l_flag, int a_flag){
    printf("%s:\n", cur_dir);
}
#include "headers.h"
#include "path.h"

void discover(char** argument_list, int argument_num){
    
    int d_flag = 0;
    int f_flag = 0;
    int search_flag = 0;
    int dir_flag = 0;

    char search_path[max_str_len];
    char dir_path[max_str_len];

    for (int i = 0; i<argument_num; i++){
        if (argument_list[i][0] == '-'){
            for (int j = 1; j < strlen(argument_list[i]); j++){
                if (argument_list[i][j] == 'd'){
                    d_flag = 1;
                } else if (argument_list[i][j] == 'f'){
                    f_flag = 1;
                } else {
                    printf("ls: No support for flag '%c'. Ignoring and proceeding...\n", argument_list[i][j]);
                }
            }
        } else if (argument_list[i][0] == '"'){

            int next_quotes = -1;
            for (int j = 1; j<strlen(argument_list[i]); j++){
                if (argument_list[i][j] == '"'){
                    next_quotes = j; //Ignores all characters after second "
                    break;
                }
            }

            if (next_quotes == -1){
                printf("Invalid argument: %s\n", argument_list[i]);
                continue;
            } else {
                argument_list[i][next_quotes] = '\0';
                strcpy(search_path, &argument_list[i][1]);
                search_flag = 1;
            }
        } else {
            dir_flag = 1;
            strcpy(dir_path, argument_list[i]); // COnsiders latest directory
        }
    }

    if (dir_flag == 0){
        strcpy(dir_path, ".");
        dir_flag = 1;
    }

    // by default search for all files and directories
    if (d_flag == 0 && f_flag == 0){
        d_flag = 1;
        f_flag = 1;
    }

    discover_ls(dir_path, d_flag, f_flag, search_flag, search_path);
}

void discover_ls(char* dir_path, int d_flag, int f_flag, int search_flag, char* search_path){
    char abs_dir_path[max_str_len];
    absolute_path(dir_path, abs_dir_path);

    char rel_dir_path[max_str_len];
    relative_path_to_cwd(dir_path, rel_dir_path);

    struct stat stat_struct;
    if (stat(abs_dir_path, &stat_struct) != 0){
        char error_string[max_str_len];
        sprintf(error_string, "discover: cannot access '%s'.", dir_path);
        perror(error_string);
        return;
    }

    if (d_flag && !search_flag){
        printf("%s\n", rel_dir_path);
    }

    DIR* dir_stream = opendir(abs_dir_path);
    if (!dir_stream){
        char error_string[max_str_len];
        sprintf(error_string, "Could not open DIR* of '%s'.", abs_dir_path);
        perror(error_string);
        return;
    }

    struct dirent* dir_struct = readdir(dir_stream);
    while(dir_struct != NULL){
        char cur_path[max_str_len];
        sprintf(cur_path, "%s/%s", abs_dir_path, dir_struct->d_name);

        if (dir_struct->d_name[0] != '.'){
            char rel_cur_path[max_str_len];
            relative_path_to_cwd(cur_path, rel_cur_path);

            stat(cur_path, &stat_struct);
            
            if (stat_struct.st_mode & S_IFDIR){
            
                if (d_flag && search_flag){
                    if (strcmp(dir_struct->d_name, search_path) == 0){
                        puts(rel_cur_path);
                    }
                }

                discover_ls(cur_path, d_flag, f_flag, search_flag, search_path);
                
            } else {
                if (f_flag){
                    if (!search_flag) puts(rel_cur_path);
                    else{
                        if (strcmp(dir_struct->d_name, search_path) == 0){
                            puts(rel_cur_path);
                        }
                    }
                }
            }

        }

        dir_struct = readdir(dir_stream);
    }
}

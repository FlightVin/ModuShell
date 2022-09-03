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
            search_flag = 1;

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
                strcpy(search_path, argument_list[i]);
            }
        } else {
            dir_flag = 1;
            strcpy(dir_path, argument_list[i]); // COnsiders latest directory
        }
    }

    if (dir_flag == 0){
        strcpy(dir_path, ".");
    }

    int is_found = 0;
    // printf("%s %s %d %d\n", dir_path, search_path, f_flag, d_flag);
    my_discover(dir_path, search_path, d_flag, f_flag, search_flag, &is_found);
}

void my_discover(char* dir_path, char* search_path, int d_flag, int f_flag, int search_flag, int* is_found){

    char absolute_dir_path[max_str_len];
    // absolute_path()

}
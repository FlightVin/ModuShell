#include "headers.h"

void relative_path(char* current_path, char* display_path){

    if (strcmp(current_path, root_dir_path) == 0){
        strcpy(display_path, "~");
        return;
    }

    size_t first_deviation = 0, min_len = strlen(root_dir_path) < strlen(current_path) ? strlen(root_dir_path) : strlen(current_path);
    while(root_dir_path[first_deviation] == current_path[first_deviation]) first_deviation++;

    if (first_deviation == strlen(root_dir_path)){
        display_path[0] = '~';
        int i = 1;
        for (int j = strlen(root_dir_path); j<strlen(current_path); i++, j++){
            display_path[i] = current_path[j];
        }
        display_path[i] = '\0';
        return;
    }

    strcpy(display_path, current_path);
}

void absolute_path(char* given_path, char* ret_path){
    if (strlen(given_path) == 0){
        strcpy(ret_path, root_dir_path);
    }else{
        if (given_path[0] == '~'){
            if (strlen(given_path) > 2){

                strcpy(ret_path, root_dir_path);
                strcat(ret_path, "/");
                strcat(ret_path, given_path);

            }else{
                strcpy(ret_path, root_dir_path);
            }
        } else if (given_path[0] == '/'){
            strcpy(ret_path, given_path);

        } else if (given_path[0] == '.' || strlen(given_path) > 1 && given_path[0] == '.' && given_path[1] == '.') {
            strcpy(ret_path, given_path);

        } else {
            getcwd(cur_dir, max_str_len);
            strcpy(ret_path, cur_dir);
            strcat(ret_path, "/");
            strcat(ret_path, given_path);
        }
    }
}
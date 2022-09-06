#include "headers.h"

void relative_path(char* current_path, char* display_path){

    if (strcmp(current_path, root_dir_path) == 0){
        strcpy(display_path, "~");
        return;
    }

    size_t first_deviation = 0, min_len = strlen(root_dir_path) < strlen(current_path) ? strlen(root_dir_path) : strlen(current_path);
    while(first_deviation < min_len && root_dir_path[first_deviation] == current_path[first_deviation]) first_deviation++;

    // checking if it was relative to root directory
    if (first_deviation == strlen(root_dir_path)){
        display_path[0] = '~';
        int i = 1;
        for (int j = strlen(root_dir_path); j<strlen(current_path); i++, j++){
            display_path[i] = current_path[j];
        }
        display_path[i] = '\0';

        if (strlen(display_path) > 1 && display_path[strlen(display_path) - 1] == '/'){
            display_path[strlen(display_path) - 1] = '\0';
        }

        return;
    }

    strcpy(display_path, current_path);
    if (strlen(display_path) > 1 && display_path[strlen(display_path) - 1] == '/'){
        display_path[strlen(display_path) - 1] = '\0';
    }
}

void absolute_path(char* given_path, char* ret_path){
    if (strlen(given_path) == 0){
        strcpy(ret_path, root_dir_path);
    }else{
        if (given_path[0] == '~'){
            if (strlen(given_path) > 2){

                strcpy(ret_path, root_dir_path);
                strcat(ret_path, "/");
                strcat(ret_path, &given_path[2]);

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

        if (strlen(ret_path) > 1 && ret_path[strlen(ret_path) - 1] == '/'){
            ret_path[strlen(ret_path) - 1] = '\0';
        }
    }
}

void relative_path_to_cwd(char* current_path, char* display_path){
    my_cwd();

    if (strcmp(current_path, cur_dir) == 0){
        strcpy(display_path, "~");
        return;
    }

    size_t first_deviation = 0, min_len = strlen(cur_dir) < strlen(current_path) ? strlen(cur_dir) : strlen(current_path);
    while(first_deviation < min_len && cur_dir[first_deviation] == current_path[first_deviation]) first_deviation++;

    // checking if it was relative to current directory
    if (first_deviation == strlen(cur_dir)){
        display_path[0] = '~';
        int i = 1;
        for (int j = strlen(cur_dir); j<strlen(current_path); i++, j++){
            display_path[i] = current_path[j];
        }
        display_path[i] = '\0';

        if (strlen(display_path) > 1 && display_path[strlen(display_path) - 1] == '/'){
            display_path[strlen(display_path) - 1] = '\0';
        }

        return;
    }

    strcpy(display_path, current_path);
    if (strlen(display_path) > 1 && display_path[strlen(display_path) - 1] == '/'){
        display_path[strlen(display_path) - 1] = '\0';
    }
}
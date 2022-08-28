#include "headers.h"

void relative_path(char* root_dir_path, char* current_path, char* display_path){

    if (strcmp(current_path, root_dir_path) == 0){
        strcpy(display_path, "~");
        return;
    }

    size_t first_deviation = 0, min_len = strlen(root_dir_path) < strlen(current_path) ? strlen(root_dir_path) : strlen(current_path);
    while(root_dir_path[first_deviation] == current_path[first_deviation]) first_deviation++;

    if (first_deviation + 1 == strlen(root_dir_path)){
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
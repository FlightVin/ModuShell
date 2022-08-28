#include "headers.h"

void relative_path(char* root_dir_path, char* current_path, char* display_path){

    if (strcmp(current_path, root_dir_path) == 0){
        strcpy(display_path, "~");
        return;
    }
    
}
#include "headers.h"

void prompt(char* root_dir_path){

    struct utsname uname_struct;
    int uname_return = uname(&uname_struct);

    if (uname_return < 0){
        throw_error("Couldn't execute uname.");
    }

    char* user_name = getenv("USER");
    char* system_name = strdup(uname_struct.sysname);
    char cur_dir[1024], display_path[1024];

    getcwd(cur_dir, 1024);

    relative_path(root_dir_path, cur_dir, display_path);

    printf("<%s@%s:%s>", user_name, system_name, display_path);
}

void relative_path(char* root_dir_path, char* current_path, char* display_path){

    if (strcmp(current_path, root_dir_path) == 0){
        strcpy(display_path, "~");
    }

    strcat(display_path, "/");

}
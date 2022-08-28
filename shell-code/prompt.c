#include "headers.h"
#include "path.h"

const size_t max_str_len = 1e3;

void prompt(char* root_dir_path){

    struct utsname uname_struct;
    int uname_return = uname(&uname_struct);

    if (uname_return < 0){
        throw_error("Couldn't execute uname.");
    }

    char* user_name = getenv("USER");
    char* system_name = strdup(uname_struct.sysname);
    char cur_dir[max_str_len], display_path[max_str_len];

    getcwd(cur_dir, 1024);

    relative_path(root_dir_path, cur_dir, display_path);

    printf(" \033[0;34m");
    printf("<%s@%s:%s>", user_name, system_name, display_path);
    printf(" \033[0m");
}


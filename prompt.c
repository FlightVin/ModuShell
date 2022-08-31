#include "headers.h"
#include "path.h"

void prompt(){

    struct utsname uname_struct;
    int uname_return = uname(&uname_struct);

    if (uname_return < 0){
        throw_error("Couldn't execute uname.");
    }

    int ret = getlogin_r(user_name, strlen(user_name));
    if (ret < 0){
        throw_error("Could not acess user name!");
    }
    char* system_name = strdup(uname_struct.sysname);
    char display_path[max_str_len];

    getcwd(cur_dir, max_str_len);

    relative_path(cur_dir, display_path);

    printf("\033[33m");
    printf("<%s@%s:%s> ", user_name, system_name, display_path);
    printf("\033[0m");
}


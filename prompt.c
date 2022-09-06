#include "headers.h"
#include "path.h"

void prompt(){

    struct utsname uname_struct;
    int uname_return = uname(&uname_struct);

    if (uname_return < 0){
        throw_error("Couldn't execute uname.");
    }

    // get username
    uid_t uid = geteuid();
    struct passwd *pw_struct = getpwuid(uid);
    if (pw_struct == NULL) user_name = strdup("CouldNotAccessUserName");
    else user_name = pw_struct->pw_name;

    // get system name
    char* system_name = strdup(uname_struct.sysname);
    char display_path[max_str_len];

    getcwd(cur_dir, max_str_len);

    // parse relative path
    relative_path(cur_dir, display_path);

    // process time string
    char process_time_promt[1000];
    if (process_exec_time >= 1) sprintf(process_time_promt, "took %lds", process_exec_time);
    else strcpy(process_time_promt, "");
    process_exec_time = 0.0;

    printf("\033[33m");
    printf("<%s@%s:%s%s> ", user_name, system_name, display_path, process_time_promt);
    printf("\033[0m");
}


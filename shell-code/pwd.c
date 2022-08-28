#include "headers.h"
#include "path.h"

void pwd(char** path, int num, char* root_dir_path){
    char cur_dir[1000];
    getcwd(cur_dir, 1000);
    char display_path[1000];

    relative_path(root_dir_path, cur_dir, display_path);

    if (display_path[0] == '~'){
        char* temp_path = NULL;
        if (strlen(display_path)>2) temp_path = strdup(&display_path[2]);

        char* user_name = getenv("USER");
        strcpy(display_path, "HOME/");
        strcat(display_path, user_name);

        if (temp_path){
            strcat(display_path, "/");
            strcat(display_path, temp_path);
        }
    }

    printf("%s\n", display_path);
}
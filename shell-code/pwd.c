#include "headers.h"
#include "path.h"

void pwd(char** path, int num){

    if (num > 0){
        printf("Enter no arguments for pwd!\n");
        return;
    }

    char cur_dir[1000];
    getcwd(cur_dir, 1000);
    /*
    // Uncomment to print relative path 
    char display_path[1000];

    relative_path(cur_dir, display_path);

    if (display_path[0] == '~'){
        char* temp_path = NULL;
        if (strlen(display_path)>2) temp_path = strdup(&display_path[2]);

        strcpy(display_path, "home/");
        strcat(display_path, user_name);

        if (temp_path){
            strcat(display_path, "/");
            strcat(display_path, temp_path);
        }
    }

    printf("%s\n", display_path);
    */
    printf("%s\n", cur_dir);
}
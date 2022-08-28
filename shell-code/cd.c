#include "headers.h"

void cd(char** path, int num, char* root_dir_path){
    if (num == 0){
        int chdir_ret = chdir(root_dir_path);

        if (chdir_ret < 0){
            printf("No such path exists!\n");
        }
    
        return;
    }

    if (num > 1){
        printf("Wrong format! Enter only one argument.\n");
        return;
    }

    if (*path[0] == '~'){

        if (strlen(*path) > 2){
            char new_path[1000];
            strcpy(new_path, root_dir_path);
            strcat(new_path, "/");
            strcat(new_path, &(*path)[1]);

            int chdir_ret = chdir(new_path);

            // printf("%s\n", new_path);

            if (chdir_ret < 0){
                printf("No such path exists!\n");
            }
        }else{
            int chdir_ret = chdir(root_dir_path);

            if (chdir_ret < 0){
                printf("No such path exists!\n");
            }
        }
    }else{
        int chdir_ret = chdir(*path);

        if (chdir_ret < 0){
            printf("No such path exists!\n");
        }
    }
}
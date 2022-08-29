#include "headers.h"

void cd(char** path, int num){


    if (num > 1){
        printf("Wrong format! Enter only one argument.\n");
        return;
    }

    getcwd(cur_dir, max_str_len);


    if (num == 0){
        int chdir_ret = chdir(root_dir_path);

        if (chdir_ret < 0){
            printf("No such path exists!\n");
            return;
        }
    } else if (*path[0] == '-'){
        if (!pwd_flag){
            printf("old_pwd doesn't exist!\n");
            return;
        }

        printf("%s\n", old_pwd);

        chdir(old_pwd);

    } else if (*path[0] == '~' || (*path[0] == '/' && strlen(*path)>2)){ // to handle both mount / and relative path

        if (*path[0] == '~' && strlen(*path) > 2){

            char new_path[1000];
            strcpy(new_path, root_dir_path);
            strcat(new_path, "/");
            strcat(new_path, &(*path)[2]);

            int chdir_ret = chdir(new_path);

            if (chdir_ret < 0){
                printf("No such path exists!\n");
                return;
            }
        } else if (*path[0] == '/') {

            char new_path[1000];
            strcpy(new_path, cur_dir);
            strcat(new_path, "/");
            strcat(new_path, &(*path)[1]);

            int chdir_ret = chdir(new_path);

            if (chdir_ret < 0){
                printf("No such path exists!\n");
                return;
            }
        } else {
            int chdir_ret = chdir(root_dir_path);

            if (chdir_ret < 0){
                printf("No such path exists!\n");
                return;
            }
        }
    }else{
        int chdir_ret = chdir(*path);

        if (chdir_ret < 0){
            printf("No such path exists!\n");
            return;
        }
    }

    strcpy(old_pwd, cur_dir);

    pwd_flag = 1;
}
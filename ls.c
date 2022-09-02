#include "headers.h"
#include "path.h"
#include "ls.h"
#include "cmd.h"

void ls(char** passed_args, int num_args){
    char* dir_names[max_arg_length];
    size_t dir_num = 0;

    int l_flag = 0;
    int a_flag = 0;
    int no_dir_flag = 1;

    for (int i = 0; i<num_args; i++){
        if (passed_args[i][0] == '-'){
            for (int j = 1; j < strlen(passed_args[i]); j++){
                if (passed_args[i][j] == 'a'){
                    a_flag = 1;
                } else if (passed_args[i][j] == 'l'){
                    l_flag = 1;
                } else {
                    printf("ls: No support for flag '%c'. Ignoring and proceeding...\n", passed_args[i][j]);
                }
            }
        } else {

            no_dir_flag = 0;
            char correct_path[max_arg_length];
            absolute_path(passed_args[i], correct_path);

            DIR* dir_ret_value = opendir(correct_path);

            if (dir_ret_value){
                dir_names[dir_num++] = strdup(correct_path);
            } else {
                char error_string[max_str_len];
                sprintf(error_string, "ls: cannot access '%s'.", correct_path);
                perror(error_string);
            }
        }
    }

    // if dir_num == 0 && no_dir then access ~
    if (dir_num == 0){
        if (no_dir_flag){
            my_cwd();
            dir_names[dir_num++] = strdup(cur_dir);
        }else{
            return;
        }
    }

    // else
    do_ls(dir_names[0], l_flag, a_flag);
    for (int i = 1; i<dir_num; i++){
        printf("\n");
        do_ls(dir_names[i], l_flag, a_flag);
    }
}

int comparator(const void* a, const void* b){
    char* l = (*(struct dirent**)a)->d_name;
    char* r = (*(struct dirent**)b)->d_name;

    return strcasecmp(l, r);
}

// Test this - ls -al /mnt ~/dir1 ./dir1 ../C-shell/dir2 dir2 kjlsd

void do_ls(char* ls_dir_path, int l_flag, int a_flag){
    // puts(ls_dir_path);

    char relative_name[max_str_len];
    relative_path(ls_dir_path, relative_name);
    printf("%s:\n", relative_name);


    DIR* dir_stream = opendir(ls_dir_path);
    if (!dir_stream){
        char error_string[max_str_len];
        sprintf(error_string, "Could not open DIR* of '%s'.", ls_dir_path);
        perror(error_string);
        return;
    }

    struct dirent* dir_list[max_arg_length];
    size_t dir_num = 0;

    struct dirent* dir_struct = readdir(dir_stream);
    while(dir_struct != NULL){
        if (dir_struct->d_name[0] == '.'){
            if (a_flag == 1){
                dir_list[dir_num++] = dir_struct;
            }
        }else{
            dir_list[dir_num++] = dir_struct;
        }

        dir_struct = readdir(dir_stream);
    }

    qsort(dir_list, dir_num, sizeof(struct dirent*), comparator);

    if (l_flag == 0){
        for (int i = 0; i<dir_num; i++){

            char cur_path[max_str_len];
            strcpy(cur_path, ls_dir_path);
            strcat(cur_path, "/");
            strcat(cur_path, dir_list[i]->d_name);

            color_print(dir_list[i], cur_path);
            printf(" ");
        }
        printf("\n");
    } else {

        size_t total_val = 0;
        struct stat stat_struct;
       
        for (int i = 0; i<dir_num; i++){

            char cur_path[max_str_len];
            strcpy(cur_path, ls_dir_path);
            strcat(cur_path, "/");
            strcat(cur_path, dir_list[i]->d_name);

            if (stat(cur_path, &stat_struct) == 0){
                total_val += stat_struct.st_blocks;
            }            
        }

        printf("total %ld\n", total_val);

        for (int i = 0; i<dir_num; i++){

            char cur_path[max_str_len];
            strcpy(cur_path, ls_dir_path);
            strcat(cur_path, "/");
            strcat(cur_path, dir_list[i]->d_name);

            if (stat(cur_path, &stat_struct) == 0){
                
                // Permisions
                if (stat_struct.st_mode & S_IFDIR) printf("d");
                else printf("-");
                
                if (stat_struct.st_mode & S_IRUSR) printf("r");
                else printf("-");

                if (stat_struct.st_mode & S_IWUSR) printf("w");
                else printf("-");

                if (stat_struct.st_mode & S_IXUSR) printf("x");
                else printf("-");

                if (stat_struct.st_mode & S_IRGRP) printf("r");
                else printf("-");

                if (stat_struct.st_mode & S_IWGRP) printf("w");
                else printf("-");

                if (stat_struct.st_mode & S_IXGRP) printf("x");
                else printf("-");

                if (stat_struct.st_mode & S_IROTH) printf("r");
                else printf("-");

                if (stat_struct.st_mode & S_IWOTH) printf("w");
                else printf("-");

                if (stat_struct.st_mode & S_IXOTH) printf("x");
                else printf("-");

                // Hardlinks
                printf(" %4ld", stat_struct.st_nlink);

                // Owndership
                printf(" %-10s %-10s", getpwuid(stat_struct.st_uid)->pw_name, getgrgid(stat_struct.st_gid)->gr_name);

                // Size
                printf(" %7ld", stat_struct.st_size); // Allocating 7 as that's the maximum on my machine

                // last modification time
                struct tm* ret_time = localtime(&stat_struct.st_mtime);
                int last_hour = ret_time->tm_hour;
                int last_min = ret_time->tm_min;

                char last_hour_str[3], last_min_str[3];
                if (last_hour < 10){
                    sprintf(last_hour_str, "%c%d", '0', last_hour);
                } else sprintf(last_hour_str, "%d", last_hour);
                if (last_min < 10){
                    sprintf(last_min_str, "%c%d", '0', last_min);
                } else sprintf(last_min_str, "%d", last_min);
                

                printf(" %s %2d %s:%s ", get_month(ret_time->tm_mon), ret_time->tm_mday, last_hour_str, last_min_str);

                color_print(dir_list[i], cur_path);
                

                printf("\n");
            } else {
                perror("Could not stat");
            }     
        }

    }

    int close_ret_value = closedir(dir_stream);
    if (close_ret_value < 0){
        char error_string[max_str_len];
        sprintf(error_string, "Could not close DIR* of '%s'.", ls_dir_path);
        perror(error_string);
    }
    
}

void color_print(struct dirent* cur_ptr, char* path){
    if (cur_ptr->d_type == DT_DIR){
        printf("\033[34m");
    } else if (cur_ptr->d_type == DT_REG){
        struct stat stat_struct;
        stat(path, &stat_struct);
        if (stat_struct.st_mode & S_IXUSR) printf("\033[32m"); // Executable files
    }
    printf("%s", cur_ptr->d_name);
    printf("\033[0m");
}
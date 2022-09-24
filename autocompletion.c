#include "headers.h"

void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

void get_input(){
    char cur_char;

    setbuf(stdout, NULL);
    enableRawMode();
    memset(input_message, '\0', max_str_len);
    int pt = 0;

    while (read(STDIN_FILENO, &cur_char, 1) == 1) {
        if (iscntrl(cur_char)){

            if (cur_char == 4){ // EOT -> ^D handler
                printf("\n");
                ctrl_d_handler();
            } else if (cur_char == 10){ // linefeed -> \n
                input_message[pt++] = cur_char;
                printf("\n");
                break;
            } else if (cur_char == 127){ // backspace
                if (pt > 0){
                    input_message[--pt] ='\0';
                    printf("\b \b");
                }
            } else if (cur_char == 9) { // tab character
                char temp_path[max_str_len];
                memset(temp_path, '\0', max_str_len);

                // printf("hehe");

                if (pt == 0 || input_message[pt - 1] == ' '){
                    my_cwd();

                    DIR* dir_stream = opendir(cur_dir);
                    if (!dir_stream){
                        char error_string[max_str_len];
                        sprintf(error_string, "Could not open DIR* of '%s'.", cur_dir);
                        perror(error_string);
                        return;
                    }

                    struct dirent* dir_list[max_arg_length];
                    size_t dir_num = 0;

                    // storing things inside directory in an array
                    struct dirent* dir_struct = readdir(dir_stream);
                    while(dir_struct != NULL){
                        if (dir_struct->d_name[0] == '.'){
                            ;
                        }else{
                            dir_list[dir_num++] = dir_struct;
                            pt = strlen(input_message);
                        }

                        dir_struct = readdir(dir_stream);
                    }

                    if (dir_num == 0){
                        ;
                    } else if (dir_num == 1){
                        // printf("\n");
                        strcat(input_message, dir_list[0]->d_name);
                        pt = strlen(input_message);
                        printf("%s", dir_list[0]->d_name);
                    } else {
                        printf("\n");
                        for (int i = 0; i<dir_num; i++){
                            printf("%s\n", dir_list[i]->d_name);
                        }
                        prompt();
                        printf("%s", input_message);
                    }

                } else {
                    int last_non_space = pt-1;
                    
                    int i = pt-1;
                    while(i >= 0 && input_message[i] != ' '){
                        last_non_space = i;
                        i--;
                    }
                    strcpy(temp_path, &input_message[last_non_space]);

                    my_cwd();

                    DIR* dir_stream = opendir(cur_dir);
                    if (!dir_stream){
                        char error_string[max_str_len];
                        sprintf(error_string, "Could not open DIR* of '%s'.", cur_dir);
                        perror(error_string);
                        return;
                    }

                    struct dirent* dir_list[max_arg_length];
                    size_t dir_num = 0;

                    // storing things inside directory in an array
                    struct dirent* dir_struct = readdir(dir_stream);
                    while(dir_struct != NULL){
                        if (dir_struct->d_name[0] == '.'){
                            ;
                        }else if (strlen(dir_struct->d_name) >= strlen(temp_path) && strncmp(temp_path, dir_struct->d_name, strlen(temp_path)) == 0){
                            dir_list[dir_num++] = dir_struct;
                            pt = strlen(input_message);
                        }

                        dir_struct = readdir(dir_stream);
                    }

                    if (dir_num == 0){
                        ;
                    } else if (dir_num == 1){                    

                        strcat(input_message, &(dir_list[0]->d_name)[strlen(temp_path)]);
                        pt = strlen(input_message);
                        printf("%s", &(dir_list[0]->d_name)[strlen(temp_path)]);
                    } else {
                        printf("\n");
                        for (int i = 0; i<dir_num; i++){
                            printf("%s\n", dir_list[i]->d_name);
                        }
                        prompt();
                        printf("%s", input_message);
                    }
                }
            } else {
                printf("%d\n", cur_char);
            }

        } else {
            input_message[pt++] = cur_char;
            printf("%c", cur_char);
        }
    }

    disableRawMode();
}
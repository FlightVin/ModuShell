#include "headers.h"

void my_strtok(char** list, int* num, char* args, char* in_data){ // tokenizer function
    list[0] = strtok(in_data, args);
    *num = 0;

    while(list[*num]){
        list[++(*num)] = strtok(NULL, args);
    }
}

void my_quit(){ // for quiting terminal
    store_history();
    exit(EXIT_SUCCESS);
}

void run_command(char* cur_command){ // running a command in foreground
    char* argument_list[max_arg_length];
    char* old_argument = strdup(cur_command);
    int num_arguments;
    my_strtok(argument_list, &num_arguments, " \n\t", cur_command);
    
    if (num_arguments == 0){
        printf("syntax error near unexpected token `;`\n");
        return;
    }
    
    char* main_command = strdup(argument_list[0]);

    if (strcmp(main_command, "echo") == 0){
        echo(&argument_list[1], num_arguments - 1);
    } else if (strcmp(main_command, "cd") == 0){
        cd(&argument_list[1], num_arguments - 1);
    } else if (strcmp(main_command, "pwd") == 0){
        pwd(&argument_list[1], num_arguments - 1);
    } else if (strcmp(main_command, "quit") == 0 || strcmp(main_command, "exit") == 0){
        my_quit();
    } else if (strcmp(main_command, "ls") == 0){
        ls(&argument_list[1], num_arguments - 1);
    } else if (strcmp(main_command, "pinfo") == 0){
        pinfo(&argument_list[1], num_arguments - 1);
    } else if (strcmp(main_command, "history") == 0){
        history(default_history_display_num);
    } else if (strcmp(main_command, "discover") == 0){
        discover(&argument_list[1], num_arguments - 1);
    }

    else {
        run_in_foreground(argument_list);
    }
}

void my_cwd(){ // puts cwd path into cur_dir
    getcwd(cur_dir, max_str_len);
}

char* parse_to_string(char** args_list, int arg_num){ // convers char** to space separated char*
    char* ret_string = (char*) malloc(sizeof(char) * max_str_len);

    strcpy(ret_string, args_list[0]);

    for (int i = 1; i<arg_num; i++){
        strcat(ret_string, " ");
        strcat(ret_string, args_list[i]);
    }

    return ret_string;
}

void ctrl_c_handler(){
    add_to_history("Force Quit", default_history_storage_size);
    printf("\n");
    my_quit();
}
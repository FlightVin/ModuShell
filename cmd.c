#include "headers.h"
#include "path.h"

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

void execute_command(char* command){
    char* pipe_list[max_arg_length];
    int num_pipes = 0;
    my_strtok(pipe_list, &num_pipes, "|", command);

    if (num_pipes == 0) return;
    if (num_pipes <= 1){
        run_command(pipe_list[0]);
        return;
    }

    int stdin_file_descriptor = dup(STDIN_FILENO), stdout_file_descriptor = dup(STDOUT_FILENO);

    for (int pipe_index = 0; pipe_index < num_pipes; pipe_index++){

        int pipe_arr[2];
        int pipe_return = pipe(pipe_arr);

        if (pipe_return < 0){
            perror("Could not make pipe");
            return;
        }

        pid_t pid = fork();

        if (pid < 0){
            perror("Could not create child");
            return;
        } else if (pid == 0){
            close(pipe_arr[0]);

            dup2(pipe_arr[1], STDOUT_FILENO);

            if (pipe_index == num_pipes - 1){
                dup2(stdout_file_descriptor, STDOUT_FILENO);
                close(stdout_file_descriptor);
            }

            run_command(pipe_list[pipe_index]);

            close(pipe_arr[1]);

            dup2(stdin_file_descriptor, STDIN_FILENO);

            // fprintf(stderr, "done child\n");

            exit(EXIT_SUCCESS);
        } 
            int process_status;
            waitpid(pid, &process_status, WUNTRACED);
            // fprintf(stderr, "Entered parent\n");

            close(pipe_arr[1]);

            if (pipe_index != num_pipes - 1) dup2(pipe_arr[0], STDIN_FILENO);
            else {
                dup2(stdin_file_descriptor, STDIN_FILENO);
                close(stdin_file_descriptor);
            }

            close(pipe_arr[0]);
    }
}

int check_for_io_redir_string(char* cmd){
    if (strcmp(cmd, ">") == 0) return 1;
    if (strcmp(cmd, "<") == 0) return 1;
    if (strcmp(cmd, ">>") == 0) return 1;
    return 0;
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

    int non_io_arguments_number = 0;

    // parsing i/o redirection
    for (int i = 0; i<num_arguments; i++){
        if (argument_list[i][0] == '>' || argument_list[i][0] == '<') break;
        non_io_arguments_number = i+1;
    }

    // i/o handling
    int write_flag = 0, read_flag = 0, append_flag = 0;
    char* write_file, *read_file, *append_file;
    char write_path[max_str_len], read_path[max_str_len], append_path[max_str_len];
    int write_file_desc, read_file_desc, append_file_desc;

    if ((num_arguments - non_io_arguments_number)%2 == 1){
        printf("Invalid redirection!\n");
        return;
    }

    for (int i = non_io_arguments_number; i<num_arguments - 1; i+=2){
        if (check_for_io_redir_string(argument_list[i+1])){
            printf("Invalid command: missing file name\n");   
            return;
        }

        if (argument_list[i][0] == '>'){
            if (strcmp(argument_list[i], ">") == 0){
                write_flag = 1;
                write_file = strdup(argument_list[i+1]);

            } else if (strcmp(argument_list[i], ">>") == 0){
                append_flag = 1;
                append_file = strdup(argument_list[i+1]);

            } else {
                printf("Unexpected operand %s\n", argument_list[i]);
                return;
            }
        } else if (strcmp(argument_list[i], "<") == 0) {
            read_flag = 1;
            read_file = strdup(argument_list[i+1]);

        }  else {
            printf("Unexpected operand %s\n", argument_list[i]);
            return;
        }
    }

    int stdin_file_descriptor = dup(STDIN_FILENO), stdout_file_descriptor = dup(STDOUT_FILENO);

    if (read_flag){
        absolute_path(read_file, read_path);
        read_file_desc = open(read_path, O_RDONLY);
        if (read_file_desc < 0){
            perror("Could not read file");
            return;
        }

        dup2(read_file_desc, STDIN_FILENO);
        close(read_file_desc);
    }

    if (write_flag){
        absolute_path(write_file, write_path);
        write_file_desc = open(write_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (read_file_desc < 0){
            perror("Could not write file");
            return;
        }

        dup2(write_file_desc, STDOUT_FILENO);
        close(write_file_desc);
    }

    if (append_flag){
        absolute_path(append_file, append_path);
        append_file_desc = open(write_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (append_file_desc < 0){
            perror("Could not append file");
            return;
        }

        dup2(append_file_desc, STDOUT_FILENO);
        close(append_file_desc);
    }

    if (strcmp(main_command, "echo") == 0){
        echo(&argument_list[1], non_io_arguments_number - 1);
    } else if (strcmp(main_command, "cd") == 0){
        cd(&argument_list[1], non_io_arguments_number - 1);
    } else if (strcmp(main_command, "pwd") == 0){
        pwd(&argument_list[1], non_io_arguments_number - 1);
    } else if (strcmp(main_command, "quit") == 0 || strcmp(main_command, "exit") == 0){
        my_quit();
    } else if (strcmp(main_command, "ls") == 0){
        ls(&argument_list[1], non_io_arguments_number - 1);
    } else if (strcmp(main_command, "pinfo") == 0){
        pinfo(&argument_list[1], non_io_arguments_number - 1);
    } else if (strcmp(main_command, "history") == 0){
        history(default_history_display_num);
    } else if (strcmp(main_command, "discover") == 0){
        discover(&argument_list[1], non_io_arguments_number - 1);
    } else if (strcmp(main_command, "jobs") == 0){
        jobs(&argument_list[1], non_io_arguments_number - 1);
    } else if (strcmp(main_command, "sig") == 0){
        sig(&argument_list[1], non_io_arguments_number - 1);
    } else if (strcmp(main_command, "bg") == 0){
        bg(&argument_list[1], non_io_arguments_number - 1);
    } else if (strcmp(main_command, "fg") == 0){
        fg(&argument_list[1], non_io_arguments_number - 1);
    }

    else {
        char* non_io_args_list[max_arg_length];
        for (int i = 0; i<non_io_arguments_number; i++) non_io_args_list[i] = strdup(argument_list[i]);
        run_in_foreground(non_io_args_list);
    }

    if (read_flag){
        dup2(stdin_file_descriptor, STDIN_FILENO);
        close(stdin_file_descriptor);
    }

    if (write_flag || append_flag){
        dup2(stdout_file_descriptor, STDOUT_FILENO);
        close(stdout_file_descriptor);
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

void ctrl_d_handler(){
    // not letting anything other than terminal handle this
    if (getpid() != shell_pid){
        printf("Only call in shell!\n");
        return;
    }

    puts("Logging out of shell");
    add_to_history("Shell Log Out", default_history_storage_size);
    printf("\n");
    my_quit();
}

void ctrl_c_handler(){
    // not letting anything other than terminal handle this
    if (getpid() != shell_pid){
        printf("Only call in shell!\n");
        return;
    }

    if (is_foreground_running){
        kill(cur_foreground_process_pid, SIGINT); // interrupting foreground process

        is_foreground_running = 0;
        printf("\n");
        fflush(stdout);
    } else {
        printf("\n");
        prompt();
        fflush(stdout);
    }
}

void ctrl_z_handler(){
    // not letting anything other than terminal handle this
    if (getpid() != shell_pid){
        printf("Only call in shell!\n");
        return;
    }

    if (is_foreground_running){
        // converting to background process
        insert_dll(running_background_processes, cur_foreground_process_pid, cur_foreground_process_name);
        printf("[%ld] %d\n", running_background_processes->size, cur_foreground_process_pid);
        setpgid(cur_foreground_process_pid, cur_foreground_process_pid);
                                                                                                                                                                                                                                                                                                                        
        kill(cur_foreground_process_pid, SIGTSTP); // changing status to stopped
        // puts(cur_foreground_process_name);

        is_foreground_running = 0;
        printf("\n");
        fflush(stdout);
    } else {
        printf("\n");
        prompt();
        fflush(stdout);
    }
}